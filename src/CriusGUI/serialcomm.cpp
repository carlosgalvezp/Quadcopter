#include "serialcomm.h"

SerialComm::SerialComm():
    active_(false)
{
    rx_buffer_ = new char[RX_BUFFER_SIZE];
    this->init();
}

SerialComm::~SerialComm()
{
    delete rx_buffer_;
    serialPort_->close();
}

void SerialComm::init()
{
    std::cout << "Initializing COM port..." << std::endl;

    // Create Serial Port object
    serialPort_ = new QSerialPort("COM4");

    // Open it
    serialPort_->open(QIODevice::ReadWrite);

    if(!serialPort_->isOpen())
    {
        std::cout << "Can't open the port" << std::endl;
    }

    // Set port properties
    serialPort_->setBaudRate(QSerialPort::Baud115200);
    serialPort_->setFlowControl(QSerialPort::NoFlowControl);
    serialPort_->setParity(QSerialPort::NoParity);
    serialPort_->setDataBits(QSerialPort::Data8);
    serialPort_->setStopBits(QSerialPort::OneStop);

    std::cout << "Everything OK!" << std::endl;
}

void SerialComm::toggleSerialComm()
{
    this->active_ = !this->active_;
}

int SerialComm::read(char * const data, int n_bytes)
{
    return this->serialPort_->read(data, n_bytes);
}

QSerialPort * SerialComm::getQSerialPort(){return this->serialPort_;}

void SerialComm::run()
{
    while(true)
    {
        if(this->active_)
        {
            // Read data
            serialPort_->waitForReadyRead(10000);
            int n_bytes = serialPort_->read(this->rx_buffer_, RX_BUFFER_SIZE);
            std::cout << "Number of read bytes: "<< n_bytes << std::endl;
//            std::cout << "Command: " << (uint8_t)rx_buffer_[0] << std::endl;
//            msleep(1000);
        }
    }
}
