// Hexapod.h

#ifndef _HEXAPOD_h
#define _HEXAPOD_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Defines.h"
#include "HexapodLeg.h"

enum
{
    LEG_COUNT = 6,
    TOTAL_SERVOS = TOTAL_SEGMENTS * LEG_COUNT
};

struct ServoPins
{
    uint8_t pins[LEG_COUNT][TOTAL_SEGMENTS];
};

class Hexapod
{
    void _Init();
protected:
    HexapodLeg * _legs[LEG_COUNT];
    uint8_t _servoPins[LEG_COUNT][TOTAL_SEGMENTS];

public:
    Hexapod() { _Init(); }

    virtual void Init() {}
    virtual void SetupLegs();
    virtual void UpdateLegs();
    virtual void AddSequence(uint8_t legID, MovementSequence * sequence)
    {
        Serial.print("Leg ");
        Serial.println(legID); _legs[legID]->AddSequence(sequence);
    }
    //virtual void SetTargetAngle(uint8_t legID, uint16_t angle) { _legs[legID]->}

};

extern Hexapod HEXAPOD;

#endif

