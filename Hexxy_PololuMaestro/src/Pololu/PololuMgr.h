#ifndef POLOLU_MGR_H
#define POLOLU_MGR_H

#include "Arduino.h"
#include "Util.h"
#include <SoftwareSerial.h>

enum
{
    PIN_POLOLU_TX       = 8,
    PIN_POLOLU_RX       = 9,
    POLOLU_PIN          = 115200
};

enum PololuCommands
{
    CMD_GET_FIRMWARE_VERSION            = 0x81,
    CMD_GET_ERROR_BYTE                  = 0x82,
    CMD_GET_CONFIG                      = 0x83,
    CMD_SET_CONFIG                      = 0x84,
    CMD_REMOVE_MSB                      = 0xF
};

class PololuMgr
{
public:
    static PololuMgr &instance()
    {
        static PololuMgr instance;
        return instance;
    }

    void setServoValue(uint8_t servoId, uint16_t value);
    void setServoValueSSC(uint8_t servoId, uint8_t value);

    void Init()
    {
    }


private:
    SoftwareSerial * _serial;
    PololuMgr();
    ~PololuMgr() {}
};

#define sPololuMgr PololuMgr::instance()

#endif