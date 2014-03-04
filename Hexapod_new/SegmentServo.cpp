// 
// 
// 

#include "SegmentServo.h"
#include "Arduino.h"

SegmentServo::SegmentServo(uint8_t servoPin, uint16_t minPulse, uint16_t maxPulse, uint8_t default_angle, uint8_t deviation) : _minPulseWidth(minPulse), _maxPulseWidth(maxPulse)
{

    _servo.attach(servoPin);

    uint16_t defWidth = CalcPulseWidth(default_angle);

    _currentAngle = defWidth;
    _targetAngle = defWidth;
    _speedFactor = 1.0f;

    deviation = CalcPulseWidth(deviation);

    _infiniteMovement = false;
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

    bool done = false;
    float speedFkt = 11.0f / 3.0f * _speedFactor;

    if (abs(_currentAngle - _targetAngle) > speedFkt)
    {
        int8_t direction = (_targetAngle < _currentAngle) ? -1 : 1;

        _currentAngle += direction  * _speedFactor;
        _servo.writeMicroseconds(_currentAngle);

        if (!_infiniteMovement &&  abs(_currentAngle - _targetAngle) <= speedFkt)
            done = true;
    } else if (!_infiniteMovement)
        done = true;

    if (done)
    {
        _moveStatus = MOVE_STATUS_STOPPED;

#ifdef HEX_LEG_DEBUG
        Serial.print(SegToText[i]);
        Serial.println(" done");
#endif
    }


    //long delta = _currentAngle - _targetAngle;
    //long deltaAbs = abs(delta);
    //uint16_t stepSpeedFactor = 11.0f / 3.0f * _speedFactor;
    //
    //
    //if (deltaAbs > stepSpeedFactor)
    //{
    //    int8_t direction = delta < 1 ? -1 : 1;
    //
    //    _currentAngle += direction * _speedFactor;
    //
    //    deltaAbs -= _speedFactor;
    //    _servo.writeMicroseconds(_currentAngle);
    //}
    //
    //// stop if we're near the target angle
    //// infinite = receiving data from controller
    //if (!_infiniteMovement && deltaAbs < stepSpeedFactor)
    //    _moveStatus = MOVE_STATUS_STOPPED;
}

void SegmentServo::StartMovement(uint8_t angleDeg, float speedFactor, bool infinite, bool forced)
{
    if (IsMoving() && !forced)
        return;

    SetTargetAngle(angleDeg);
    _speedFactor = speedFactor > 0.0f ? speedFactor : 1.0f;
    _moveStatus = MOVE_STATUS_MOVING;
    _infiniteMovement = infinite;
}

//SegmentServo SEGMENTSERVO;

