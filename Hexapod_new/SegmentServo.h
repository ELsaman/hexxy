// SegmentServo.cpp.h

#ifndef _SEGMENTSERVO_h
#define _SEGMENTSERVO_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Util.h"
#include "Defines.h"
#include <ServoNew.h>

class SegmentServo
{
 private:
     // Pulse widths, not degrees!
     uint16_t _currentAngle;
     uint16_t _targetAngle;

     uint8_t _deviation;
     uint16_t _minPulseWidth;
     uint16_t _maxPulseWidth;

     float _speedFactor;

     uint16_t CalcPulseWidth(uint8_t angle) const { return DEG_TO_PULSE(angle, _minPulseWidth, _maxPulseWidth); }

     Servo _servo;
     bool _infiniteMovement;

     MoveStatus _moveStatus;

 public:
	void init();
    SegmentServo(uint8_t servoPin, uint16_t minPulse = DEFAULT_MIN_MICROS, uint16_t maxPulse = DEFAULT_MAX_MICROS, uint8_t default_angle = 90, uint8_t deviationDeg = 0);
    SegmentServo();

    uint16_t GetCurrentAngle() const { return _currentAngle; }
    uint16_t GetTargetAngle() const { return _targetAngle; }

    uint8_t GetCurrentAngleDeg() const { return PULSE_TO_DEG(_currentAngle, _minPulseWidth, _maxPulseWidth); }
    uint8_t GetTargetAngleDeg() const { return PULSE_TO_DEG(_targetAngle, _minPulseWidth, _maxPulseWidth); }

    void SetPulseWidthBounds(uint16_t minWidth, uint16_t maxWidth) { _minPulseWidth = minWidth; _maxPulseWidth = maxWidth; }
    void SetTargetAngle(uint8_t angleDeg) { _targetAngle = CalcPulseWidth(angleDeg) + _deviation; }
    void StartMovement(uint8_t angleDeg, float speedFactor = 1.0f, bool infinite = false, bool forced = false);
    void StopMovement() { _moveStatus = MOVE_STATUS_STOPPED; }

    bool IsMoving() const { return _moveStatus == MOVE_STATUS_MOVING; }

    void Update();

};

extern SegmentServo SEGMENTSERVO;

#endif

