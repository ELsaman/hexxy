#include "PololuMgr.h"

PololuMgr::PololuMgr()
{
    _serial = &Serial2;
    _serial->begin(POLOLU_PIN);
    //_serial = new SoftwareSerial(PIN_POLOLU_RX, PIN_POLOLU_TX, false);
    //_serial->begin(POLOLU_PIN);
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

// OxFF, Servo number, servo value (0 - 255)
void PololuMgr::setServoValueSSC(uint8_t servoId, uint8_t value)
{
    byte buffer[3] = { 0 };

    buffer[0] = 0xFF;
    buffer[1] = servoId;
    buffer[2] = value;

    _serial->write(buffer, ARRAY_SIZE(buffer));
}