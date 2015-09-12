#ifndef SERIALCOMMTHREAD_H
#define SERIALCOMMTHREAD_H

#include <QObject>
#include <QSerialPort>
#include <QTimer>

#include <iostream>

#include "../ArduinoFC/Telemetry_Protocol.h"

#define TX_BUFFER_SIZE  10
#define RX_BUFFER_SIZE  100

#define UPDATE_RATE_STATUS  25      // Hz

class SerialCommThread : public QObject
{
    Q_OBJECT

public:
    SerialCommThread();
    ~SerialCommThread();

public slots:
    void process();

signals:
    void sendData(const QByteArray &data);

private slots:
    void requestStatus();
    void readData();
private:

    void init();

    void updateStatus(const char * const dataIn);

    QSerialPort* serialPort_;
    QTimer* timer_Status_;

    char dataOut[TX_BUFFER_SIZE];
    char dataIn[RX_BUFFER_SIZE];

    const char * magic_word_ = TELEMETRY_MAGIC_WORD;

};

#endif // SERIALCOMMTHREAD_H
