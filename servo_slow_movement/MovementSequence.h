#ifndef MOV_SEQ_H
#define MOV_SEQ_H

#include "stdint.h"
#include "Defines.h"
#include "HardwareSerial.h"
#include <vector>
#include <deque>

struct Movement
{
    //Movement() : angle(0), speed(0.0f), delay(0) {}

    Movement(uint16_t _angle, float _speed, uint16_t _delay, bool inversed = false) : angle(calcAngle(_angle, inversed)), speed(_speed), delay(_delay) {}
    uint16_t angle;
    float speed;
    uint16_t delay;

//    uint16_t calcAngle(uint16_t angle, bool inversed) { return (inversed && angle != 90) ? angle - 90 : angle; }

    static uint16_t calcAngle(int16_t angle, bool inversed) {
        if (!inversed || angle == 90)
        {
            //if (angle != 90)
            //    Serial.println(" not inversed");
            return angle;
        }

        //Serial.println(angle);
        //Serial.println(inversed);

        int diff = angle - 90;

        //char buf[255];
        //sprintf(buf, " Angle: %i, diff: %i, out angle: %i", angle, diff, 90 - diff);
        //Serial.println(buf);

        return 90 - diff;

        //angle -= 90;
        //
        //if (angle < 0)
        //    return 180 + angle;
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

        //movement[SEGMENT_TIBIA].push_back(Movement(90, 2.0f, 1000, _inversed));
        //movement[SEGMENT_FEMUR].push_back(Movement(80, 2.0f, 1000, _inversed));
        //movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, 1000, _inversed));
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
        //Serial.print("TargetedMovement: angle ");
        //Serial.println(_angle);
        //Serial.flush();
        movement[SEGMENT_TIBIA].push_back(Movement(80, 5.0f, 1000, _inversed));
        movement[SEGMENT_FEMUR].push_back(Movement(80, 5.0f, 1000, _inversed));
        movement[SEGMENT_COXA].push_back(Movement(_angle, 2.0f, 1000, false));
    };
private:
    uint16_t _angle;
};

typedef std::vector<MovementSequence> SequenceContainer;

#endif // !