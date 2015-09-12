#include "serialdecoder.h"

bool SerialDecoder::decodeData(const QByteArray &data, GUIData &gui_data)
{
    // Verify magic word
    if (data[0] == this->magic_word_[0] && data[1] == this->magic_word_[1])
    {
        // Get command
        char cmd = data[2];

        // Decode data
        switch(cmd)
        {
            case TELEMETRY_CMD_OUT_STATUS:
                return this->decodeStatus(data, gui_data);
        }
    }
    return false; // Failed to detect the magic word
}


bool SerialDecoder::decodeStatus(const QByteArray &data, GUIData &gui_data)
{
    gui_data.timeStamp = ((((uint32_t)data[3]) << 24) & 0xFF000000) |
                         ((((uint32_t)data[4]) << 16) & 0x00FF0000) |
                         ((((uint32_t)data[5]) << 8)  & 0x0000FF00) |
                         ((((uint32_t)data[6]))       & 0x000000FF);

    return true;
}
