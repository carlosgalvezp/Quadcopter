#include "criusgui.h"
#include "ui_criusgui.h"

#include "serialcommthread.h"

CriusGUI::CriusGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CriusGUI),
    active_(false),
    connected_(false)
{
    // Create SerialCommThread
    SerialCommThread* serial_thread = new SerialCommThread();
    QThread*  thread = new QThread;
    serial_thread->moveToThread(thread);
    connect(thread, SIGNAL(started()), serial_thread, SLOT(init()));

    connect(this, SIGNAL(loadFCConfig()), serial_thread, SLOT(requestConfig()));
    connect(this, SIGNAL(sendFCConfig(QByteArray)), serial_thread, SLOT(sendConfig(QByteArray)));
    connect(this, SIGNAL(sendSerialConfig(QString,QString)), serial_thread, SLOT(connectSerial(QString,QString)));
    connect(this, SIGNAL(sendSerialDisconnect()), serial_thread, SLOT(disconnectSerial()));

    connect(serial_thread, SIGNAL(sendData(QByteArray)), this, SLOT(getSerialData(QByteArray)));
    connect(serial_thread, SIGNAL(sendSerialPortInfo(QStringList)), this, SLOT(receiveSerialPortInfo(QStringList)));
    connect(this, SIGNAL(sendGotACK()), serial_thread, SLOT(receiveACK()));

    thread->start();

    // Setup UI
    ui->setupUi(this);

    // Initialize plots
    this->imu_plot= new TimePlot(this->ui->imu_plot,  this->ui->imu_plot->geometry().width()/2, 6);
    this->control_plot = new TimePlot(this->ui->control_plot,  this->ui->control_plot->geometry().width()/2, 4);
}

CriusGUI::~CriusGUI()
{
    delete ui;
}

void CriusGUI::getSerialData(const QByteArray &data)
{
    // Store data in buffer
    for(unsigned char c : data) this->rx_data_buffer_.push_back(c);

    // Decode available packages
    this->serial_decoder_.decodeBuffer(this->rx_data_buffer_, this->gui_data_);

    // Update GUI
    this->updateGUI();
}

void CriusGUI::updateGUI()
{
    // Status
    if(this->gui_data_.new_status)
    {
        this->ui->data_in_timeStamp->setText(QString::number(this->gui_data_.status.timeStamp));
        this->ui->data_in_cycleTime->setText(QString::number(this->gui_data_.status.cycleTime));

        this->ui->data_in_battery_voltage->setText(QString::number(this->gui_data_.status.battery.voltage));
        this->ui->data_in_battery_current->setText(QString::number(this->gui_data_.status.battery.current));

        this->gui_data_.new_status = false;
    }

    // RC readings
    if(this->gui_data_.new_RC)
    {
        this->ui->data_in_throttle->setText(QString::number(this->gui_data_.rc_data.throttle));
        this->ui->data_in_rudder->setText(QString::number(this->gui_data_.rc_data.rudder));
        this->ui->data_in_elevator->setText(QString::number(this->gui_data_.rc_data.elevator));
        this->ui->data_in_aileron->setText(QString::number(this->gui_data_.rc_data.aileron));
        this->ui->data_in_aux1->setText(QString::number(this->gui_data_.rc_data.aux1));
        this->ui->data_in_aux2->setText(QString::number(this->gui_data_.rc_data.aux2));
        this->ui->data_in_aux3->setText(QString::number(this->gui_data_.rc_data.aux3));
        this->ui->data_in_aux4->setText(QString::number(this->gui_data_.rc_data.aux4));

        this->gui_data_.new_RC = false;
    }

    // IMU
    if(this->gui_data_.new_IMU_data)
    {
        this->imu_plot->addPoint({(double)gui_data_.imu_data.acc.x,
                                  (double)gui_data_.imu_data.acc.y,
                                  (double)gui_data_.imu_data.acc.z,});

        this->gui_data_.new_IMU_data = false;
    }

    // Attitude
    if(this->gui_data_.new_attitude)
    {
        double roll, pitch, yaw;
        Utils::quaternionToRPY(this->gui_data_.attitude.q0,
                               this->gui_data_.attitude.q1,
                               this->gui_data_.attitude.q2,
                               this->gui_data_.attitude.q3,
                               &roll, &pitch, &yaw);

        this->ui->data_in_roll->setText(QString::number(roll));
        this->ui->data_in_pitch->setText(QString::number(pitch));
        this->ui->data_in_yaw->setText(QString::number(yaw));

        this->ui->myGLWidget->updateRotation(-roll, -pitch);

        this->gui_data_.new_attitude = false;
    }

    // Control input
    if(this->gui_data_.new_motors)
    {
        this->control_plot->addPoint({(double)this->gui_data_.motors[0],
                                      (double)this->gui_data_.motors[1],
                                      (double)this->gui_data_.motors[2],
                                      (double)this->gui_data_.motors[3]});

        this->gui_data_.new_motors = false;
    }

    // Config
    if(this->gui_data_.new_config)
    {
        // PID config
        this->ui->Config_PID_Roll_KP->setText(QString::number(gui_data_.config.pid_roll.kp));
        this->ui->Config_PID_Roll_KD->setText(QString::number(gui_data_.config.pid_roll.kd));
        this->ui->Config_PID_Roll_KI->setText(QString::number(gui_data_.config.pid_roll.ki));

        this->ui->Config_PID_Pitch_KP->setText(QString::number(gui_data_.config.pid_pitch.kp));
        this->ui->Config_PID_Pitch_KD->setText(QString::number(gui_data_.config.pid_pitch.kd));
        this->ui->Config_PID_Pitch_KI->setText(QString::number(gui_data_.config.pid_pitch.ki));

        this->ui->Config_PID_Yaw_KP->setText(QString::number(gui_data_.config.pid_yaw.kp));
        this->ui->Config_PID_Yaw_KD->setText(QString::number(gui_data_.config.pid_yaw.kd));
        this->ui->Config_PID_Yaw_KI->setText(QString::number(gui_data_.config.pid_yaw.ki));

        this->gui_data_.new_config = false;
    }

    // Received ACK
    if(this->gui_data_.gotACK)
    {
        // Tell serial thread not to reSend config
        emit sendGotACK();

        // Set button to green to inform the user
        QPalette pal = this->ui->PushButton_Config_Send->palette();
        pal.setColor(QPalette::Button, QColor(Qt::green));
        this->ui->PushButton_Config_Send->setAutoFillBackground(true);
        this->ui->PushButton_Config_Send->setPalette(pal);
        this->ui->PushButton_Config_Send->update();

        this->gui_data_.gotACK = false;
    }
}

void CriusGUI::on_PushButton_Config_Load_clicked()
{
    emit loadFCConfig(); // Call Serial Communication thread
}

void CriusGUI::on_PushButton_Config_Send_clicked()
{
    // Set default color on the button
    QPalette pal = this->ui->PushButton_Config_Send->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    this->ui->PushButton_Config_Send->setAutoFillBackground(true);
    this->ui->PushButton_Config_Send->setPalette(pal);
    this->ui->PushButton_Config_Send->update();

    // Update gui_data with the lastest configuration
    this->gui_data_.config.pid_roll.kp = this->ui->Config_PID_Roll_KP->toPlainText().toFloat();
    this->gui_data_.config.pid_roll.kd = this->ui->Config_PID_Roll_KD->toPlainText().toFloat();
    this->gui_data_.config.pid_roll.ki = this->ui->Config_PID_Roll_KI->toPlainText().toFloat();

    this->gui_data_.config.pid_pitch.kp = this->ui->Config_PID_Pitch_KP->toPlainText().toFloat();
    this->gui_data_.config.pid_pitch.kd = this->ui->Config_PID_Pitch_KD->toPlainText().toFloat();
    this->gui_data_.config.pid_pitch.ki = this->ui->Config_PID_Pitch_KI->toPlainText().toFloat();

    this->gui_data_.config.pid_yaw.kp = this->ui->Config_PID_Yaw_KP->toPlainText().toFloat();
    this->gui_data_.config.pid_yaw.kd = this->ui->Config_PID_Yaw_KD->toPlainText().toFloat();
    this->gui_data_.config.pid_yaw.ki = this->ui->Config_PID_Yaw_KI->toPlainText().toFloat();


    QByteArray data;
    this->gui_data_.config.serialize(data);

    emit sendFCConfig(data);
}

void CriusGUI::on_pushButton_Connect_clicked()
{
    if(!this->connected_)
    {
        this->connected_ = true;
        this->ui->pushButton_Connect->setText("Disconnect");

        emit sendSerialConfig(this->ui->comboBox_PortName->currentText(), this->ui->comboBox_BaudRate->currentText());
    }
    else
    {
        this->connected_ = false;
        this->ui->pushButton_Connect->setText("Connect");

        emit sendSerialDisconnect();
    }
}

void CriusGUI::receiveSerialPortInfo(const QStringList &port_names)
{
    // Set port names
    for (int i = 0; i < port_names.size(); ++i)
    {
        this->ui->comboBox_PortName->insertItem(i, port_names[i]);
    }

    // Set baud rate (for now, fixed)
    this->ui->comboBox_BaudRate->insertItem(0, "115200");

}
