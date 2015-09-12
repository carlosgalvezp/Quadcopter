#ifndef SERIALDECODER_H
#define SERIALDECODER_H

#include <iostream>

#include <QByteArray>
#include "guidata.h"

#include "../ArduinoFC/Telemetry_Protocol.h"


class SerialDecoder
{
public:
    bool decodeData(const QByteArray &data, GUIData &gui_data);

private:
    const char * magic_word_ = TELEMETRY_MAGIC_WORD;
    uint8_t checkSum_;

    bool verifyCheckSum(const QByteArray &data);

    bool decodeStatus(const QByteArray &data, GUIData &gui_data);

};

#endif // SERIALDECODER_H
