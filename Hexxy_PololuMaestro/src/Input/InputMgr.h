#ifndef INPUT_MGR_H
#define INPUT_MGR_H

#include "Arduino.h"
#include "IKCalculator.h"

struct InputState
{
    InputState() : _speedX(0), _speedY(0), _rotation() {}
    //InputState(float angle, float speed, float rotation) : _angle(angle), _speedFkt(speed), _rotation(rotation) {}

    /// <summary>
    /// Initializes Input State with the data received from serial
    /// </summary>
    /// <param name="angleDeg">Strafe movement angle in degrees.</param>
    /// <param name="speedX10">Movement speed * 10.</param>
    /// <param name="rotationDeg">Body rotation angle in degrees.</param>
    InputState(int speedX, int speedY, IKBodyMods bodyMod) : _speedX(speedX), _speedY(speedY), _rotation(bodyMod)
    {
        //_angle = angle;
        //_speedFkt = speed;
        //_rotation = bodyMod;
    }

    int getSpeedX() const { return _speedX; }
    int getSpeedY() const { return _speedY; }

    bool isMoving() const
    {
        return true;
        return abs(_speedX) > 20 || abs(_speedY) > 20;
    }
    //float getAngle() { return _angle; }
    //float getSpeedFkt() { return _speedFkt; }
    const IKBodyMods * getRotation()  { return &_rotation; }

private:
    int _speedX;
    int _speedY;
    //float _speedFkt;
    IKBodyMods _rotation;
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