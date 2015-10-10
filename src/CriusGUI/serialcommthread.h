#ifndef SERIALCOMMTHREAD_H
#define SERIALCOMMTHREAD_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QTimer>
#include <QStringList>

#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

#include "../ArduinoFC/Telemetry_Protocol.h"

#define TX_BUFFER_SIZE  10
#define RX_BUFFER_SIZE  100

#define UPDATE_RATE_STATUS          10      // Hz
#define UPDATE_RATE_IMU             25      // Hz
#define UPDATE_RATE_RC              20      // Hz
#define UPDATE_RATE_ATTITUDE        50      // Hz
#define UPDATE_RATE_CONTROL         50      // Hz

#define T_REQUEST_WAIT_MS    5

#define my_sleep_ms(t) std::this_thread::sleep_for(std::chrono::milliseconds(t))


class SerialCommThread : public QObject
{
    Q_OBJECT

public:
    SerialCommThread();
    ~SerialCommThread();

public slots:
    void init();
    void connectSerial(const QString &portName, const QString &baud_rate);
    void disconnectSerial();
    void requestConfig();
    void sendConfig(const QByteArray &data);

signals:
    void sendSerialPortInfo(const QStringList &port_names);
    void sendData(const QByteArray &data);

private slots:
    void requestStatus();
    void requestRC();
    void requestIMU();
    void requestAttitude();
    void requestMotors();

    void readData();
private:
    void updateStatus(const char * const dataIn);
    void requestCmd(uint8_t cmd);

    QSerialPort* serialPort_;
    std::vector<QTimer *> timers_;
    const std::vector<uint8_t> timer_frequencies = { UPDATE_RATE_STATUS,
                                                     UPDATE_RATE_RC,
                                                     UPDATE_RATE_IMU,
                                                     UPDATE_RATE_ATTITUDE,
                                                     UPDATE_RATE_CONTROL};
    std::vector<const char*> timer_fncs = {SLOT(requestStatus()),
                                           SLOT(requestRC()),
                                           SLOT(requestIMU()),
                                           SLOT(requestAttitude()),
                                           SLOT(requestMotors())};
    const std::vector<bool> timer_on = {1, 0, 1, 1, 0};


    char dataOut[TX_BUFFER_SIZE];
    char dataIn[RX_BUFFER_SIZE];

    const char * magic_word_ = TELEMETRY_MAGIC_WORD;

};

#endif // SERIALCOMMTHREAD_H
