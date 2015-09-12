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

    std::cout << "Started Serial Comm Thread Process" << std::endl;

}

void SerialCommThread::init()
{
    std::cout << "Initializing COM port..." << std::endl;

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

    std::cout << "Everything OK!" << std::endl;

    // ** Initialize timers
    this->timer_Status_ = new QTimer(this);
    connect(this->timer_Status_, SIGNAL(timeout()), this, SLOT(requestStatus()));
    this->timer_Status_->start(1000.0 / UPDATE_RATE_STATUS);


    // ** Read interruption
    connect(this->serialPort_, SIGNAL(readyRead()), this, SLOT(readData()));
}

void SerialCommThread::requestStatus()
{
    std::cout << "Requesting status..." << std::endl;
    this->dataOut[0] = this->magic_word_[0];
    this->dataOut[1] = this->magic_word_[1];
    this->dataOut[2] = TELEMETRY_CMD_OUT_STATUS;
    this->serialPort_->write(this->dataOut, 3);
}

void SerialCommThread::readData()
{
    int n_bytes = this->serialPort_->read(this->dataIn, RX_BUFFER_SIZE);
    std::cout << "I have read " << n_bytes << " bytes" << std::endl;

    QByteArray out_array(this->dataIn, n_bytes);

    emit sendData(out_array);
}
