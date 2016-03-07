#ifndef SERIALDECODER_H
#define SERIALDECODER_H

#include <iostream>

#include <QByteArray>
#include <QQueue>
#include "guidata.h"

#include "../ArduinoFC/Telemetry_Protocol.h"


class SerialDecoder
{
public:
    bool decodeBuffer(QQueue<unsigned char> &buffer, GUIData &gui_data);

private:
    const char * magic_word_ = TELEMETRY_MAGIC_WORD;
    uint8_t checkSum_;

    const float K_VOLTAGE_TO_VOLTS =       10.0f  * (5.0f / 1023.0f);
    const float K_CURRENT_TO_AMPS  = (1.0f/0.05f) * (5.0f / 1023.0f);

    bool decodeData(const QByteArray &data, GUIData &gui_data);
    void extractCompleteFrames(QQueue<unsigned char> &buffer, std::vector<QByteArray> &packages);

    bool verifyCheckSum(const QByteArray &data);

    bool decodeStatus   (const QByteArray &data, GUIData &gui_data);
    bool decodeRC       (const QByteArray &data, GUIData &gui_data);
    bool decodeIMU      (const QByteArray &data, GUIData &gui_data);
    bool decodeAttitude (const QByteArray &data, GUIData &gui_data);
    bool decodeMotors   (const QByteArray &data, GUIData &gui_data);
    bool decodeConfig   (const QByteArray &data, GUIData &gui_data);

    uint16_t decode16(const QByteArray &data, int ptr);
    uint32_t decode32(const QByteArray &data, int ptr);
    float decodeFloat(const QByteArray &data, int ptr);

};

#endif // SERIALDECODER_H
