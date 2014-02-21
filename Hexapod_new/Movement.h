// Movement.h

#ifndef _MOVEMENT_h
#define _MOVEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif


struct Movement
{
public:
    Movement(uint16_t _angle, float _speed, uint16_t _delay, bool inversed = false) : speed(_speed), delay(_delay)
    {
        angle = CalcAngle(_angle, inversed);
    }

    // returns angle mirrored to 90° if the inversed = true (60° -> 120°) 
    static uint16_t CalcAngle(uint16_t angle, bool inversed)
    {
        if (!inversed || angle == 90)
            return angle;

        return 90 - (angle - 90);
    }

    uint16_t angle;
    float speed;
    uint16_t delay;
};

#endif

