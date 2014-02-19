#ifndef HEXA_LEG_SEG
#define HEXA_LEG_SEG
#include <Servo.h>
//#include "C:\arduino-1.0.1\Arduino\libraries\Servo\Servo.h"

struct HexaLegSegment
{
    HexaLegSegment() {}
    HexaLegSegment(uint8_t pin, int * valArray, bool digital, int degree);

    void move(int val) { servo->writeMicroseconds(val); }

    void reattach() { servo->attach(pin); }
    void detach() { servo->detach(); }

    unsigned int current_angle;
    unsigned int target_angle;
    bool moveStatus;
    float speedMod;
    bool isDigital;
    uint8_t pin;

private:
    Servo * servo;
};

#endif