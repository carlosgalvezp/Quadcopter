#include "serialcommthread.h"

SerialCommThread::SerialCommThread():
    serialPort_(nullptr)
{
}

SerialCommThread::~SerialCommThread()
{
    delete serialPort_;
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
            timers_.push_back(timer);

            connect(timer, SIGNAL(timeout()), this, timer_fncs_[i]);
            timer->start(1000.0 / timer_frequencies_[i]);
        }
    }

    // ** Read interruption
    connect(serialPort_, SIGNAL(readyRead()), this, SLOT(readData()));

    // ** Request FC config
    requestConfig();
}

void SerialCommThread::disconnectSerial()
{
    // Delete serial port
    serialPort_->close();
    delete serialPort_;

    // Delete timers
    for (QTimer * t : timers_)
    {
        t->stop();
        delete t;
    }

    // Clear timer vector
    timers_.clear();
}

void SerialCommThread::requestStatus()
{
    requestCmd(TELEMETRY_CMD_OUT_STATUS);
}

void SerialCommThread::requestRC()
{
    requestCmd(TELEMETRY_CMD_OUT_RC);
}

void SerialCommThread::requestIMU()
{
    requestCmd(TELEMETRY_CMD_OUT_IMU);
}

void SerialCommThread::requestAttitude()
{
    requestCmd(TELEMETRY_CMD_OUT_ATTITUDE);
}

void SerialCommThread::requestMotors()
{
    requestCmd(TELEMETRY_CMD_OUT_CONTROL);
}

void SerialCommThread::requestConfig()
{
    requestCmd(TELEMETRY_CMD_OUT_CONFIG);
}

void SerialCommThread::receiveACK()
{
    reSendConfig_ = false;
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
    dataOut[0] = magic_word_[0];     checksum ^= dataOut[0];
    dataOut[1] = magic_word_[1];     checksum ^= dataOut[1];
    dataOut[2] = TELEMETRY_CMD_IN_CONFIG;  checksum ^= dataOut[2];

    // Fill data
    for(int i = 0; i < data.size(); ++i)
    {
        dataOut[3+i] = data[i];
        checksum ^= data[i];
    }

    dataOut[data_size - 1] = checksum;

    // Send
    serialPort_->write(dataOut, data_size);

    // Start timer: if we don't receive an ACK, re-send the data
    configToReSend_ = data;
    reSendConfig_ = true;
    QTimer::singleShot(T_CONFIG_ACK_WAIT_MS, this, SLOT(reSendConfig()));
}

void SerialCommThread::requestCmd(uint8_t cmd)
{
    // Fill data buffer
    dataOut[0] = magic_word_[0];
    dataOut[1] = magic_word_[1];
    dataOut[2] = cmd;

    // Write to serial port
    serialPort_->write(dataOut, 3);
}

void SerialCommThread::readData()
{
    emit sendData(serialPort_->readAll());
}


