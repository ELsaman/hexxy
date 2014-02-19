#ifndef MOV_SEQ_H
#define MOV_SEQ_H

#include "stdint.h"
#include "Defines.h"
#include "HardwareSerial.h"
#include <vector>
#include <deque>

struct Movement
{
    Movement(uint16_t _angle, float _speed, uint16_t _delay, bool inversed = false) : angle(calcAngle(_angle, inversed)), speed(_speed), delay(_delay) {}
    uint16_t angle;
    float speed;
    uint16_t delay;

    static uint16_t calcAngle(int16_t angle, bool inversed) {
        if (!inversed || angle == 90)
        {
            return angle;
        }

        int diff = angle - 90;

        return 90 - diff;
    }
};

struct MovementSequence
{
    MovementSequence(bool inversed, bool infinite = false);
    virtual ~MovementSequence() {}

    virtual void Init();

    bool HasSequence(uint8_t index) { return !(movement[index].empty()); }
    const Movement * GetNextSequence(uint8_t index) const { return &movement[index].front(); }
    void ClearTop(uint8_t index) { movement[index].pop_front(); }
    bool _infinite;

protected:
    std::deque<Movement> movement[TOTAL_SEGMENTS];
    bool _inversed;
};

struct DebugResetMovement : public MovementSequence
{
    DebugResetMovement(bool inversed) : MovementSequence(inversed) {}

    void Init();
};

struct StandupMovement : public MovementSequence
{
    StandupMovement(bool inversed) : MovementSequence(inversed) {}

    void Init()
    {
        Serial.println("StandupMovement init");
        movement[SEGMENT_TIBIA].push_back(Movement(90, 2.0f, 1000, _inversed));
        movement[SEGMENT_FEMUR].push_back(Movement(90, 2.0f, 1000, _inversed));
        movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, 1000, _inversed));
    };
};

struct TargetedMovement : public MovementSequence
{
    TargetedMovement(bool inversed, uint16_t angle) : MovementSequence(inversed)
    {
        _angle = angle;
        _inversed = inversed;
        _infinite = true;
    }

    void Init()
    {
        movement[SEGMENT_TIBIA].push_back(Movement(80, 5.0f, 1000, _inversed));
        movement[SEGMENT_FEMUR].push_back(Movement(80, 5.0f, 1000, _inversed));
        movement[SEGMENT_COXA].push_back(Movement(_angle, 2.0f, 1000, false));
    };
private:
    uint16_t _angle;
};

typedef std::vector<MovementSequence> SequenceContainer;

#endif // !