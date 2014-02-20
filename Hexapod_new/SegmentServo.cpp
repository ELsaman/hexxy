// 
// 
// 

#include "SegmentServo.h"

SegmentServo::SegmentServo(uint8_t servoPin, uint16_t minPulse, uint16_t maxPulse, uint8_t default_angle, uint8_t deviation) : _minPulseWidth(minPulse), _maxPulseWidth(maxPulse)
{
    _servo.attach(servoPin);

    uint16_t defWidth = CalcPulseWidth(default_angle);

    _currentAngle = defWidth;
    _targetAngle = defWidth;

    deviation = CalcPulseWidth(deviation);

    _moveStatus = MOVE_STATUS_MOVING;
}

/*
Move servo to _targetAngle
With specified speed (0 > speed > infinity)
occurs only if width delta is bigger than 
*/
void SegmentServo::Update()
{
    if (!IsMoving())
        return;

    int16_t delta = abs(_currentAngle - _targetAngle);
    uint16_t stepSpeedFactor = 11.0f / 3 * _speedFactor;

    if (delta > stepSpeedFactor)
    {
        int8_t direction = delta > 1 ? -1 : 1;

        _currentAngle += direction * _speedFactor;
        delta -= _speedFactor;
        _servo.writeMicroseconds(_currentAngle);
    }

    // stop if we're near the target angle
    // infinite = receiving data from controller
    if (!_infiniteMovement && delta < stepSpeedFactor)
        _moveStatus = MOVE_STATUS_STOPPED;
}

void SegmentServo::StartMovement(uint8_t angleDeg, float speedFactor, bool infinite, bool forced)
{
    if (IsMoving() && !forced)
        return;

    SetTargetAngle(angleDeg);
    _speedFactor = speedFactor > 0.0f ? speedFactor : 1.0f;
    _moveStatus = MOVE_STATUS_MOVING;
    _infiniteMovement = true;
}

void SegmentServo::init()
{


}


//SegmentServo SEGMENTSERVO;

