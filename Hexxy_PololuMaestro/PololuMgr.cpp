#include "PololuMgr.h"

PololuMgr::PololuMgr()
{
    _serial = new SoftwareSerial(PIN_POLOLU_RX, PIN_POLOLU_TX, false);
    _serial->begin(POLOLU_PIN);
}

void PololuMgr::setServoValue(uint8_t servoId, uint16_t value)
{
    byte buffer[4] = { 0 };

    buffer[0] = CMD_SET_CONFIG;
    buffer[1] = servoId;
    buffer[2] = value & 0b01111111;
    buffer[3] = (value >> 7) & 0b01111111;

    _serial->write(buffer, ARRAY_SIZE(buffer));
}