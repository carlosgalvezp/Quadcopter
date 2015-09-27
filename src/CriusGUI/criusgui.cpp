#include "criusgui.h"
#include "ui_criusgui.h"

#include "serialcommthread.h"

CriusGUI::CriusGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CriusGUI),
    active_(false)
{
    // Create SerialCommThread
    SerialCommThread* serial_thread = new SerialCommThread();
    QThread*  thread = new QThread;
    serial_thread->moveToThread(thread);
    connect(thread, SIGNAL(started()), serial_thread, SLOT(process()));
    connect(this, SIGNAL(loadFCConfig()), serial_thread, SLOT(requestConfig()));
    connect(serial_thread, SIGNAL(sendData(QByteArray)), this, SLOT(getSerialData(QByteArray)));

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
    this->serial_decoder_.decodeData(data, this->gui_data_);
    this->updateGUI();
}

void CriusGUI::on_pushButton_clicked()
{
    // Toggle active and change button text
    this->active_ = !this->active_;
    if(this->active_)
    {
        ui->pushButton->setText("Stop");
    }
    else
    {
        ui->pushButton->setText("Start");
    }
}

void CriusGUI::updateGUI()
{
    // Status
    if(this->gui_data_.new_status)
    {
        this->ui->data_in_timeStamp->setText(QString::number(this->gui_data_.status.timeStamp));
        this->ui->data_in_cycleTime->setText(QString::number(this->gui_data_.status.cycleTime));

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
}

void CriusGUI::on_PushButton_Config_Load_clicked()
{
    emit loadFCConfig(); // Call Serial Communication thread
}
