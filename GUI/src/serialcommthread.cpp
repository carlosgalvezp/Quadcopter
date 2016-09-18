#include "serialcommthread.h"

SerialCommThread::SerialCommThread():
    serialPort_(nullptr)
{
}

SerialCommThread::~SerialCommThread()
{
    delete this->serialPort_;
}

void SerialCommThread::init()
{
    // Send information to GUI
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    QStringList data_out;
    for (const QSerialPortInfo& p : ports)
    {
        data_out.push_back(p.portName());
    }

    emit sendSerialPortInfo(data_out);
}

void SerialCommThread::connectSerial(const QString &portName)
{
    // Create Serial Port object
    serialPort_ = new QSerialPort(portName, this);

    // Open it
    serialPort_->open(QIODevice::ReadWrite);  // Arduino resets now
    my_sleep_ms(2000);  // To ensure Arduino has finished booting up!

    if(!serialPort_->isOpen())
    {
        std::cout << "Can't open the port" << std::endl;
        delete serialPort_;
        return;
    }

    // Set port properties
    serialPort_->setBaudRate(QSerialPort::Baud115200);
    serialPort_->setFlowControl(QSerialPort::NoFlowControl);
    serialPort_->setParity(QSerialPort::NoParity);
    serialPort_->setDataBits(QSerialPort::Data8);
    serialPort_->setStopBits(QSerialPort::OneStop);


    // ** Initialize timers
    for (std::size_t i = 0; i < timer_on_.size(); ++i)
    {
        if (timer_on_[i])
        {
            QTimer* timer = new QTimer(this);
            this->timers_.push_back(timer);

            connect(timer, SIGNAL(timeout()), this, this->timer_fncs_[i]);
            timer->start(1000.0 / timer_frequencies_[i]);
        }
    }

    // ** Read interruption
    connect(this->serialPort_, SIGNAL(readyRead()), this, SLOT(readData()));

    // ** Request FC config
    this->requestConfig();
}

void SerialCommThread::disconnectSerial()
{
    // Delete serial port
    this->serialPort_->close();
    delete this->serialPort_;

    // Delete timers
    for (QTimer * t : this->timers_)
    {
        t->stop();
        delete t;
    }

    // Clear timer vector
    this->timers_.clear();
}

void SerialCommThread::requestStatus()
{
    this->requestCmd(TELEMETRY_CMD_OUT_STATUS);
}

void SerialCommThread::requestRC()
{
    this->requestCmd(TELEMETRY_CMD_OUT_RC);
}

void SerialCommThread::requestIMU()
{
    this->requestCmd(TELEMETRY_CMD_OUT_IMU);
}

void SerialCommThread::requestAttitude()
{
    this->requestCmd(TELEMETRY_CMD_OUT_ATTITUDE);
}

void SerialCommThread::requestMotors()
{
    this->requestCmd(TELEMETRY_CMD_OUT_CONTROL);
}

void SerialCommThread::requestConfig()
{
    this->requestCmd(TELEMETRY_CMD_OUT_CONFIG);
}

void SerialCommThread::receiveACK()
{
    this->reSendConfig_ = false;
}

void SerialCommThread::reSendConfig()
{
    if(reSendConfig_)
    {
        sendConfig(configToReSend_);
    }
}

void SerialCommThread::sendConfig(const QByteArray &data)
{
    // Define package size
    uint8_t data_size = 4 + data.size(); // Header(3) + data + checksum(1)
    uint8_t checksum = 0;

    // Fill header
    this->dataOut[0] = this->magic_word_[0];     checksum ^= this->dataOut[0];
    this->dataOut[1] = this->magic_word_[1];     checksum ^= this->dataOut[1];
    this->dataOut[2] = TELEMETRY_CMD_IN_CONFIG;  checksum ^= this->dataOut[2];

    // Fill data
    for(int i = 0; i < data.size(); ++i)
    {
        this->dataOut[3+i] = data[i];
        checksum ^= data[i];
    }

    this->dataOut[data_size - 1] = checksum;

    // Send
    this->serialPort_->write(this->dataOut, data_size);

    // Start timer: if we don't receive an ACK, re-send the data
    configToReSend_ = data;
    reSendConfig_ = true;
    QTimer::singleShot(T_CONFIG_ACK_WAIT_MS, this, SLOT(reSendConfig()));
}

void SerialCommThread::requestCmd(uint8_t cmd)
{
    // Fill data buffer
    this->dataOut[0] = this->magic_word_[0];
    this->dataOut[1] = this->magic_word_[1];
    this->dataOut[2] = cmd;

    // Write to serial port
    this->serialPort_->write(this->dataOut, 3);
}

void SerialCommThread::readData()
{
    emit sendData(this->serialPort_->readAll());
}


