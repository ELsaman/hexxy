#ifndef GAIT_H
#define GAIT_H

#include "Arduino.h"

class Gait
{

public:
    Gait(uint8_t steps, float speed = 1.0f) : _stepCount(steps), _speedMod(speed) {}

    void SetSpeed(float speedMod) { _speedMod = speedMod; }

    Gait() {}
    ~Gait() {}

private:
    float _speedMod;
    uint8_t _stepCount;
};

#endif