#include "serialcommthread.h"

SerialCommThread::SerialCommThread()
{
}

SerialCommThread::~SerialCommThread()
{
    delete this->serialPort_;
}

void SerialCommThread::process()
{
    this->init();
}

void SerialCommThread::init()
{
    std::cout << "Initializing COM port...";

    // Create Serial Port object
    serialPort_ = new QSerialPort("COM4", this);

    // Open it
    serialPort_->open(QIODevice::ReadWrite);

    if(!serialPort_->isOpen())
    {
        std::cout << "Can't open the port" << std::endl;
        return;
    }

    // Set port properties
    serialPort_->setBaudRate(QSerialPort::Baud115200);
    serialPort_->setFlowControl(QSerialPort::NoFlowControl);
    serialPort_->setParity(QSerialPort::NoParity);
    serialPort_->setDataBits(QSerialPort::Data8);
    serialPort_->setStopBits(QSerialPort::OneStop);

    std::cout << "OK" << std::endl;
    // ** Initialize timers
    this->timer_Status_ = new QTimer(this);
    connect(this->timer_Status_, SIGNAL(timeout()), this, SLOT(requestStatus()));
    this->timer_Status_->start(1000.0 / UPDATE_RATE_STATUS);


    this->timer_RC_ = new QTimer(this);
    connect(this->timer_RC_, SIGNAL(timeout()), this, SLOT(requestRC()));
    this->timer_RC_->start(1000.0 / UPDATE_RATE_RC);

    this->timer_Attitude = new QTimer(this);
    connect(this->timer_Attitude , SIGNAL(timeout()), this, SLOT(requestAttitude()));
    this->timer_Attitude ->start(1000.0 / UPDATE_RATE_ATTITUDE);


    // ** Read interruption
    connect(this->serialPort_, SIGNAL(readyRead()), this, SLOT(readData()));
}

void SerialCommThread::requestStatus()
{
    this->writeHeader(this->dataOut, TELEMETRY_CMD_OUT_STATUS);
    this->serialPort_->write(this->dataOut, 3);
}

void SerialCommThread::requestRC()
{
    this->writeHeader(this->dataOut, TELEMETRY_CMD_OUT_RC);
    this->serialPort_->write(this->dataOut, 3);
}

void SerialCommThread::requestAttitude()
{
    this->writeHeader(this->dataOut, TELEMETRY_CMD_OUT_ATTITUDE);
    this->serialPort_->write(this->dataOut, 3);
}

void SerialCommThread::writeHeader(char * const buffer, uint8_t cmd)
{
    buffer[0] = this->magic_word_[0];
    buffer[1] = this->magic_word_[1];
    buffer[2] = cmd;
}

void SerialCommThread::readData()
{
    int n_bytes = this->serialPort_->read(this->dataIn, RX_BUFFER_SIZE);
    QByteArray out_array(this->dataIn, n_bytes);

    emit sendData(out_array);
}
