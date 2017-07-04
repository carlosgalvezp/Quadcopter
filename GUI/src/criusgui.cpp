#include "criusgui.h"
#include "ui_criusgui.h"

#include "serialcommthread.h"

CriusGUI::CriusGUI(QWidget *parent) :
    QMainWindow(parent),
    ui_(new Ui::CriusGUI),
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
    connect(this, SIGNAL(sendSerialConfig(QString)),
            serial_thread,
            SLOT(connectSerial(QString)));
    connect(this, SIGNAL(sendSerialDisconnect()), serial_thread, SLOT(disconnectSerial()));

    connect(serial_thread, SIGNAL(sendData(QByteArray)), this, SLOT(getSerialData(QByteArray)));
    connect(serial_thread, SIGNAL(sendSerialPortInfo(QStringList)), this, SLOT(receiveSerialPortInfo(QStringList)));
    connect(this, SIGNAL(sendGotACK()), serial_thread, SLOT(receiveACK()));

    thread->start();

    // Setup UI
    ui_->setupUi(this);

    // Initialize plots
    imu_plot_= new TimePlot(ui_->imu_plot, ui_->imu_plot->geometry().width()/2, 6);
    control_plot_ = new TimePlot(ui_->control_plot,  ui_->control_plot->geometry().width()/2, 4);
}

CriusGUI::~CriusGUI()
{
    delete ui_;
}

void CriusGUI::getSerialData(const QByteArray &data)
{
    // Store data in buffer
    for(unsigned char c : data) rx_data_buffer_.push_back(c);

    // Decode available packages
    serial_decoder_.decodeBuffer(rx_data_buffer_, gui_data_);

    // Update GUI
    updateGUI();
}

void CriusGUI::updateGUI()
{
    // Status
    if(gui_data_.new_status)
    {
        ui_->data_in_timeStamp->setText(QString::number(gui_data_.status.timeStamp));
        ui_->data_in_cycleTime->setText(QString::number(gui_data_.status.cycleTime));

        ui_->data_in_battery_voltage->setText(QString::number(gui_data_.status.battery.voltage));
        ui_->data_in_battery_current->setText(QString::number(gui_data_.status.battery.current));

        ui_->data_in_FlightMode->setText(flightModeMap_[gui_data_.status.flightMode]);

        gui_data_.new_status = false;
    }

    // RC readings
    if(gui_data_.new_RC)
    {
        ui_->data_in_throttle->setText(QString::number(gui_data_.rc_data.throttle));
        ui_->data_in_rudder->setText(QString::number(gui_data_.rc_data.rudder));
        ui_->data_in_elevator->setText(QString::number(gui_data_.rc_data.elevator));
        ui_->data_in_aileron->setText(QString::number(gui_data_.rc_data.aileron));
        ui_->data_in_aux1->setText(QString::number(gui_data_.rc_data.aux1));
        ui_->data_in_aux2->setText(QString::number(gui_data_.rc_data.aux2));
        ui_->data_in_aux3->setText(QString::number(gui_data_.rc_data.aux3));
        ui_->data_in_aux4->setText(QString::number(gui_data_.rc_data.aux4));

        gui_data_.new_RC = false;
    }

    // IMU
    if(gui_data_.new_IMU_data)
    {
        imu_plot_->addPoint({(double)gui_data_.imu_data.acc.x,
                             (double)gui_data_.imu_data.acc.y,
                             (double)gui_data_.imu_data.acc.z,});

        gui_data_.new_IMU_data = false;
    }

    // Attitude
    if(gui_data_.new_attitude)
    {
        double roll, pitch, yaw;
        Utils::quaternionToRPY(gui_data_.attitude.q0,
                               gui_data_.attitude.q1,
                               gui_data_.attitude.q2,
                               gui_data_.attitude.q3,
                               &roll, &pitch, &yaw);

        ui_->data_in_roll->setText(QString::number(roll));
        ui_->data_in_pitch->setText(QString::number(pitch));
        ui_->data_in_yaw->setText(QString::number(yaw));

        gui_data_.new_attitude = false;
    }

    // Control input
    if(gui_data_.new_motors)
    {
        control_plot_->addPoint({(double)gui_data_.motors[0],
                                 (double)gui_data_.motors[1],
                                 (double)gui_data_.motors[2],
                                 (double)gui_data_.motors[3]});

        gui_data_.new_motors = false;
    }

    // Config
    if(gui_data_.new_config)
    {
        // PID config
        ui_->Config_PID_Roll_KP->setText(QString::number(gui_data_.config.pid_roll.kp));
        ui_->Config_PID_Roll_KD->setText(QString::number(gui_data_.config.pid_roll.kd));
        ui_->Config_PID_Roll_KI->setText(QString::number(gui_data_.config.pid_roll.ki));

        ui_->Config_PID_Pitch_KP->setText(QString::number(gui_data_.config.pid_pitch.kp));
        ui_->Config_PID_Pitch_KD->setText(QString::number(gui_data_.config.pid_pitch.kd));
        ui_->Config_PID_Pitch_KI->setText(QString::number(gui_data_.config.pid_pitch.ki));

        ui_->Config_PID_Yaw_KP->setText(QString::number(gui_data_.config.pid_yaw.kp));
        ui_->Config_PID_Yaw_KD->setText(QString::number(gui_data_.config.pid_yaw.kd));
        ui_->Config_PID_Yaw_KI->setText(QString::number(gui_data_.config.pid_yaw.ki));

        gui_data_.new_config = false;
    }

    // Received ACK
    if(gui_data_.gotACK)
    {
        // Tell serial thread not to reSend config
        emit sendGotACK();

        // Set button to green to inform the user
        QPalette pal = ui_->PushButton_Config_Send->palette();
        pal.setColor(QPalette::Button, QColor(Qt::green));
        ui_->PushButton_Config_Send->setAutoFillBackground(true);
        ui_->PushButton_Config_Send->setPalette(pal);
        ui_->PushButton_Config_Send->update();

        gui_data_.gotACK = false;
    }
}

void CriusGUI::on_PushButton_Config_Load_clicked()
{
    emit loadFCConfig(); // Call Serial Communication thread
}

void CriusGUI::on_PushButton_Config_Send_clicked()
{
    // Set default color on the button
    QPalette pal = ui_->PushButton_Config_Send->palette();
    pal.setColor(QPalette::Button, QColor(Qt::white));
    ui_->PushButton_Config_Send->setAutoFillBackground(true);
    ui_->PushButton_Config_Send->setPalette(pal);
    ui_->PushButton_Config_Send->update();

    // Update gui_data with the lastest configuration
    gui_data_.config.pid_roll.kp = ui_->Config_PID_Roll_KP->toPlainText().toFloat();
    gui_data_.config.pid_roll.kd = ui_->Config_PID_Roll_KD->toPlainText().toFloat();
    gui_data_.config.pid_roll.ki = ui_->Config_PID_Roll_KI->toPlainText().toFloat();

    gui_data_.config.pid_pitch.kp = ui_->Config_PID_Pitch_KP->toPlainText().toFloat();
    gui_data_.config.pid_pitch.kd = ui_->Config_PID_Pitch_KD->toPlainText().toFloat();
    gui_data_.config.pid_pitch.ki = ui_->Config_PID_Pitch_KI->toPlainText().toFloat();

    gui_data_.config.pid_yaw.kp = ui_->Config_PID_Yaw_KP->toPlainText().toFloat();
    gui_data_.config.pid_yaw.kd = ui_->Config_PID_Yaw_KD->toPlainText().toFloat();
    gui_data_.config.pid_yaw.ki = ui_->Config_PID_Yaw_KI->toPlainText().toFloat();


    QByteArray data;
    gui_data_.config.serialize(data);

    emit sendFCConfig(data);
}

void CriusGUI::on_pushButton_Connect_clicked()
{
    if(!connected_)
    {
        connected_ = true;
        ui_->pushButton_Connect->setText("Disconnect");

        emit sendSerialConfig(ui_->comboBox_PortName->currentText());
    }
    else
    {
        connected_ = false;
        ui_->pushButton_Connect->setText("Connect");

        emit sendSerialDisconnect();
    }
}

void CriusGUI::receiveSerialPortInfo(const QStringList &port_names)
{
    // Set port names
    for (int i = 0; i < port_names.size(); ++i)
    {
        ui_->comboBox_PortName->insertItem(i, port_names[port_names.size() - 1U - i]);
    }

    // Set baud rate (for now, fixed)
    ui_->comboBox_BaudRate->insertItem(0, "115200");
}
