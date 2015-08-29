#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <QThread>

#include <iostream>
#include <stdint.h>

#define RX_BUFFER_SIZE 100

class SerialComm : public QThread
{
    Q_OBJECT // Required to implement own signals/slots
public:
    SerialComm();
    ~SerialComm();

    void init();
    int read(char * const data, int n_bytes);
    QSerialPort *  getQSerialPort();
    void run();

public slots:
    void toggleSerialComm();

private:
QSerialPort * serialPort_;
char * rx_buffer_;
bool active_;
};

#endif // SERIALCOMM_H
