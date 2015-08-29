#include "criusgui.h"
#include "ui_criusgui.h"



CriusGUI::CriusGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CriusGUI),
    active_(false)
{
    // Create serialPort and connect to receive slot
    this->serialPort_ = new SerialComm();
    QObject::connect(serialPort_->getQSerialPort(), SIGNAL(readyRead()), this, SLOT(receiveData()));


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

void CriusGUI::receiveData()
{
    char rx_buffer[RX_BUFFER_SIZE];
    int n_bytes = this->serialPort_->read(rx_buffer, RX_BUFFER_SIZE);

    if (n_bytes == 13 && rx_buffer[0] == 1)
    {
        int16_t acc_x = ((((int16_t)rx_buffer[1]) << 8) & 0xFF00) | ((int16_t)rx_buffer[2] & 0x00FF);
        int16_t acc_y = ((((int16_t)rx_buffer[3]) << 8) & 0xFF00) | ((int16_t)rx_buffer[4] & 0x00FF);
        int16_t acc_z = ((((int16_t)rx_buffer[5]) << 8) & 0xFF00) | ((int16_t)rx_buffer[6] & 0x00FF);

        int16_t gyro_x = ((((int16_t)rx_buffer[7]) << 8) & 0xFF00) | ((int16_t)rx_buffer[8] & 0x00FF);
        int16_t gyro_y = ((((int16_t)rx_buffer[9]) << 8) & 0xFF00) | ((int16_t)rx_buffer[10] & 0x00FF);
        int16_t gyro_z = ((((int16_t)rx_buffer[11]) << 8) & 0xFF00) | ((int16_t)rx_buffer[12] & 0x00FF);

        ui->data_in_acc_x->setText(QString::number(acc_x));
        ui->data_in_acc_y->setText(QString::number(acc_y));
        ui->data_in_acc_z->setText(QString::number(acc_z));

        ui->data_in_gyro_x->setText(QString::number(gyro_x));
        ui->data_in_gyro_y->setText(QString::number(gyro_y));
        ui->data_in_gyro_z->setText(QString::number(gyro_z));

        this->acc_plot_->addPoint({acc_x, acc_y, acc_z});
        this->gyro_plot_->addPoint({gyro_x, gyro_y, gyro_z});
    }
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
    // Emit signal to the Serial Communication thread
    emit toggleSerial();
}

void CriusGUI::refresh()
{
//    repaint();
}
