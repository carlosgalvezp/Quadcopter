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

void SerialCommThread::connectSerial(const QString &portName, const QString &baud_rate)
{
    std::cout << "Connecting to serial port " << portName.toStdString()<<std::endl;
    // Create Serial Port object
    serialPort_ = new QSerialPort(portName, this);

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


    // ** Initialize timers
    for (std::size_t i = 0; i < timer_on.size(); ++i)
    {
        if (timer_on[i])
        {
            this->timers_.push_back(new QTimer(this));
            QTimer* timer = this->timers_.back();

            connect(timer, SIGNAL(timeout()), this, this->timer_fncs[i]);
            timer->start(1000.0 / timer_frequencies[i]);
        }
    }


//    this->timer_Status_ = new QTimer(this);
//    connect(this->timer_Status_, SIGNAL(timeout()), this, SLOT(requestStatus()));
//    this->timer_Status_->start(1000.0 / UPDATE_RATE_STATUS);

//    this->timer_RC_ = new QTimer(this);
//    connect(this->timer_RC_, SIGNAL(timeout()), this, SLOT(requestRC()));
//    this->timer_RC_->start(1000.0 / UPDATE_RATE_RC);

//    this->timer_IMU = new QTimer(this);
//    connect(this->timer_IMU, SIGNAL(timeout()), this, SLOT(requestIMU()));
//    this->timer_IMU->start(1000.0 / UPDATE_RATE_IMU);

//    this->timer_Attitude = new QTimer(this);
//    connect(this->timer_Attitude , SIGNAL(timeout()), this, SLOT(requestAttitude()));
//    this->timer_Attitude ->start(1000.0 / UPDATE_RATE_ATTITUDE);

//    this->timer_control = new QTimer(this);
//    connect(this->timer_control, SIGNAL(timeout()), this, SLOT(requestMotors()));
//    this->timer_control->start(1000.0 / UPDATE_RATE_CONTROL);

    // ** Read interruption
    connect(this->serialPort_, SIGNAL(readyRead()), this, SLOT(readData()));
}

void SerialCommThread::disconnectSerial()
{
    // Delete serial port
    delete this->serialPort_;

    // Delete timers
    for (QTimer * t : this->timers_)
    {
        delete t;
    }
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

void SerialCommThread::sendConfig(const QByteArray &data)
{
    // Define package size
    uint8_t data_size = 4 + data.size(); // Header + data + checksum
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
    QByteArray out_array = this->serialPort_->readAll();
    std::cout << "READ BYTES: " << out_array.size() <<std::endl;

    emit sendData(out_array);
}


