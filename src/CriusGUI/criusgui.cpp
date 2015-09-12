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
    connect(serial_thread, SIGNAL(sendData(QByteArray)), this, SLOT(getSerialData(QByteArray)));
    thread->start();



    // Setup UI
    ui->setupUi(this);

    // Initialize plots
    this->acc_plot_  = new TimePlot(ui->acc_plot,  ui->acc_plot->geometry().width(), 3);
    this->gyro_plot_ = new TimePlot(ui->gyro_plot, ui->gyro_plot->geometry().width(), 3);
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
    this->ui->data_in_timeStamp->setText(QString::number(this->gui_data_.timeStamp));
}


//void CriusGUI::telemetryCmdIMU(const char * const rx_data, int n_read_bytes)
//{
//    if (n_read_bytes == TELEMETRY_CMD_IMU_N_BYTES)
//    {
//        int16_t acc_x = ((((int16_t)rx_data[1]) << 8) & 0xFF00) | ((int16_t)rx_data[2] & 0x00FF);
//        int16_t acc_y = ((((int16_t)rx_data[3]) << 8) & 0xFF00) | ((int16_t)rx_data[4] & 0x00FF);
//        int16_t acc_z = ((((int16_t)rx_data[5]) << 8) & 0xFF00) | ((int16_t)rx_data[6] & 0x00FF);

//        int16_t gyro_x = ((((int16_t)rx_data[7]) << 8) & 0xFF00) | ((int16_t)rx_data[8] & 0x00FF);
//        int16_t gyro_y = ((((int16_t)rx_data[9]) << 8) & 0xFF00) | ((int16_t)rx_data[10] & 0x00FF);
//        int16_t gyro_z = ((((int16_t)rx_data[11]) << 8) & 0xFF00) | ((int16_t)rx_data[12] & 0x00FF);

//        this->ui->data_in_acc_x->setText(QString::number(acc_x));
//        this->ui->data_in_acc_y->setText(QString::number(acc_y));
//        this->ui->data_in_acc_z->setText(QString::number(acc_z));

//        this->ui->data_in_gyro_x->setText(QString::number(gyro_x));
//        this->ui->data_in_gyro_y->setText(QString::number(gyro_y));
//        this->ui->data_in_gyro_z->setText(QString::number(gyro_z));

//        this->acc_plot_->addPoint({(double)acc_x, (double)acc_y, (double)acc_z});
//        this->gyro_plot_->addPoint({(double)gyro_x, (double)gyro_y, (double)gyro_z});
//    }
//}

//void CriusGUI::telemetryCmdAttitude(const char * const rx_data, int n_read_bytes)
//{
//    if (n_read_bytes == TELEMETRY_CMD_ATTITUDE_N_BYTES)
//    {
//        int16_t q0_rx = ((((int16_t)rx_data[1]) << 8) & 0xFF00) | ((int16_t)rx_data[2] & 0x00FF);
//        int16_t q1_rx = ((((int16_t)rx_data[3]) << 8) & 0xFF00) | ((int16_t)rx_data[4] & 0x00FF);
//        int16_t q2_rx = ((((int16_t)rx_data[5]) << 8) & 0xFF00) | ((int16_t)rx_data[6] & 0x00FF);
//        int16_t q3_rx = ((((int16_t)rx_data[7]) << 8) & 0xFF00) | ((int16_t)rx_data[8] & 0x00FF);

//        double q0 = 0.0001 * q0_rx;
//        double q1 = 0.0001 * q1_rx;
//        double q2 = 0.0001 * q2_rx;
//        double q3 = 0.0001 * q3_rx;

//        this->ui->data_in_q0->setText(QString::number(q0));
//        this->ui->data_in_q1->setText(QString::number(q1));
//        this->ui->data_in_q2->setText(QString::number(q2));
//        this->ui->data_in_q3->setText(QString::number(q3));

//        // Get RPY
//        double roll, pitch, yaw;
//        Utils::quaternionToRPY(q0,q1,q2,q3, &roll, &pitch, &yaw);

//        this->ui->data_in_roll->setText(QString::number(roll));
//        this->ui->data_in_pitch->setText(QString::number(pitch));
//        this->ui->data_in_yaw->setText(QString::number(yaw));

//        this->ui->myGLWidget->updateRotation(roll, pitch);
//    }
//}

