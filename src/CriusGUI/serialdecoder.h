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

    bool decodeStatus   (const QByteArray &data, GUIData &gui_data);
    bool decodeRC       (const QByteArray &data, GUIData &gui_data);
    bool decodeIMU      (const QByteArray &data, GUIData &gui_data);
    bool decodeAttitude (const QByteArray &data, GUIData &gui_data);
    bool decodeMotors   (const QByteArray &data, GUIData &gui_data);

    uint16_t decode16(const QByteArray &data, int ptr);
    uint32_t decode32(const QByteArray &data, int ptr);

};

#endif // SERIALDECODER_H
