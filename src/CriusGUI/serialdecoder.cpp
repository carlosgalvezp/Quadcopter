#include "serialdecoder.h"

bool SerialDecoder::decodeData(const QByteArray &data, GUIData &gui_data)
{
    // Verify checkSum
    if(!verifyCheckSum(data)) return false;


    // Verify magic word
    if (data[0] == this->magic_word_[0] && data[1] == this->magic_word_[1])
    {
        // Get command
        uint8_t cmd = (uint8_t)data[2];

        // Decode data
        switch(cmd)
        {
            case TELEMETRY_CMD_OUT_STATUS:
                return this->decodeStatus(data, gui_data);

            case TELEMETRY_CMD_OUT_RC:
                return this->decodeRC(data, gui_data);

            case TELEMETRY_CMD_OUT_IMU:
                return this->decodeIMU(data, gui_data);

            case TELEMETRY_CMD_OUT_ATTITUDE:
                return this->decodeAttitude(data, gui_data);

        }
    }
    return false; // Failed to detect the magic word
}

bool SerialDecoder::verifyCheckSum(const QByteArray &data)
{
    uint8_t checksum = 0;
    for(int i = 0; i < data.size(); ++i)
    {
        checksum ^= (uint8_t)(data[i]);
    }
    return checksum == 0;
}


bool SerialDecoder::decodeStatus(const QByteArray &data, GUIData &gui_data)
{
    gui_data.status.timeStamp = decode32(data, 3);
    gui_data.status.cycleTime = decode16(data, 7);

    gui_data.new_status = true;
    return true;
}

bool SerialDecoder::decodeRC(const QByteArray &data, GUIData &gui_data)
{
    gui_data.rc_data.throttle = decode16(data, 3);
    gui_data.rc_data.rudder   = decode16(data, 5);
    gui_data.rc_data.elevator = decode16(data, 7);
    gui_data.rc_data.aileron  = decode16(data, 9);
    gui_data.rc_data.aux1     = decode16(data, 11);
    gui_data.rc_data.aux2     = decode16(data, 13);
    gui_data.rc_data.aux3     = decode16(data, 15);
    gui_data.rc_data.aux4     = decode16(data, 17);

    gui_data.new_RC = true;
    return true;
}

bool SerialDecoder::decodeIMU(const QByteArray &data, GUIData &gui_data)
{
    gui_data.imu_data.acc.x = (int16_t)decode16(data, 3);
    gui_data.imu_data.acc.y = (int16_t)decode16(data, 5);
    gui_data.imu_data.acc.z = (int16_t)decode16(data, 7);

    gui_data.imu_data.gyro.x = (int16_t)decode16(data, 9);
    gui_data.imu_data.gyro.x = (int16_t)decode16(data, 11);
    gui_data.imu_data.gyro.x = (int16_t)decode16(data, 13);

    gui_data.new_IMU_data = true;
    return true;
}

bool SerialDecoder::decodeAttitude(const QByteArray &data, GUIData &gui_data)
{
    gui_data.attitude.q0 = 0.0001 * ((int16_t) decode16(data, 3));
    gui_data.attitude.q1 = 0.0001 * ((int16_t) decode16(data, 5));
    gui_data.attitude.q2 = 0.0001 * ((int16_t) decode16(data, 7));
    gui_data.attitude.q3 = 0.0001 * ((int16_t) decode16(data, 9));

    gui_data.new_attitude = true;
    return true;
}

uint16_t SerialDecoder::decode16(const QByteArray &data, int ptr)
{
    return ((((uint16_t)data[ptr])   << 8) & 0xFF00) |
           ((((uint16_t)data[ptr+1]))      & 0x00FF);
}

uint32_t SerialDecoder::decode32(const QByteArray &data, int ptr)
{
    return  ((((uint32_t)data[ptr])   << 24) & 0xFF000000) |
            ((((uint32_t)data[ptr+1]) << 16) & 0x00FF0000) |
            ((((uint32_t)data[ptr+2]) << 8)  & 0x0000FF00) |
            ((((uint32_t)data[ptr+3]))       & 0x000000FF);
}
