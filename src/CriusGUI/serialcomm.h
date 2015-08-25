#ifndef SERIALCOMM_H
#define SERIALCOMM_H

#include <QSerialPort>
#include <QSerialPortInfo>
#include <iostream>

class SerialComm
{
public:
    SerialComm();
    ~SerialComm();

    void init();

private:
QSerialPort * serialPort_;

};

#endif // SERIALCOMM_H
