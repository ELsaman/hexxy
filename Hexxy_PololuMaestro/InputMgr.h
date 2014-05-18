#ifndef INPUT_MGR_H
#define INPUT_MGR_H

#include "Arduino.h"

struct InputState
{
    InputState() : _angle(0.0f), _speedFkt(0.0f), _rotation(0.0f) {}
    //InputState(float angle, float speed, float rotation) : _angle(angle), _speedFkt(speed), _rotation(rotation) {}

    /// <summary>
    /// Initializes Input State with the data received from serial
    /// </summary>
    /// <param name="angleDeg">Strafe movement angle in degrees.</param>
    /// <param name="speedX10">Movement speed * 10.</param>
    /// <param name="rotationDeg">Body rotation angle in degrees.</param>
    InputState(uint16_t angleDeg, uint16_t speedX10, uint16_t rotationDeg)
    {
        _angle = float(angleDeg) * DEG_TO_RAD;
        _speedFkt = float(speedX10) / 10.0f;
        _rotation = float(rotationDeg) * DEG_TO_RAD;
    }

    float getAngle() { return _angle; }
    float getSpeedFkt() { return _speedFkt; }
    float getRotation() { return _rotation; }

private:
    float _angle;
    float _speedFkt;
    float _rotation;
};

class InputMgr
{
public:
    static InputMgr & instance()
    {
        static InputMgr instance;
        return instance;
    };

    void setCurrentState(InputState state) { _curState = _idle ? InputState() : state; }
     InputState * getCurrentState() { return _idle ? NULL : &_curState; }

    bool isIdle() const { return _idle; }
    void setIdle(bool idle) { _idle = idle; }

private:
    bool _idle;
    InputState _curState;
    InputMgr() {};
    ~InputMgr() {};
};

#define sInputMgr InputMgr::instance()
#endif