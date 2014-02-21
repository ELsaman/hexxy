#include "MovementSequence.h"
#include "Arduino.h"

MovementSequence::MovementSequence(bool inversed, bool infinite)
{
    for (int i=0; i<3; ++i)
        movement[i].clear();

    _inversed = inversed;
    _infinite = infinite;
}

void MovementSequence::Init()
{
    int delay = 3000;
    float speed = 1.0f;
    Serial.println("MovementSequence init");
    /*movement[SEGMENT_TIBIA].push_back(Movement(90, 0.3f, 0, _inversed));
    movement[SEGMENT_FEMUR].push_back(Movement(90, 0.3f, 0, _inversed));
    movement[SEGMENT_COXA].push_back(Movement(90, 0.3f, 0, _inversed));
    bool inversed = false;
    for (int i = 0; i < 8; ++i)
    {
        movement[SEGMENT_TIBIA].push_back(Movement(90, speed, delay, _inversed));
        movement[SEGMENT_FEMUR].push_back(Movement(20, speed, delay, _inversed));
        movement[SEGMENT_COXA].push_back(Movement(90, speed, delay, inversed));

        movement[SEGMENT_TIBIA].push_back(Movement(120, speed, delay, _inversed));
        movement[SEGMENT_FEMUR].push_back(Movement(60, speed, delay, _inversed));
        movement[SEGMENT_COXA].push_back(Movement(45, speed, delay, inversed));

        movement[SEGMENT_TIBIA].push_back(Movement(120, 3.0f, 2000, _inversed));
        movement[SEGMENT_FEMUR].push_back(Movement(60, 3.0f, 2000, _inversed));
        movement[SEGMENT_COXA].push_back(Movement(155, 3.0f, 2000, inversed));
    }*/
}

/* RANDOM TEST STUFF */

void DebugResetMovement::Init()
{
    Serial.println("DebugResetMovement init");

    int delay = 8000;

    delay = 300000;

    movement[SEGMENT_TIBIA].push_back(Movement(90, 5.0f, delay, _inversed));
    movement[SEGMENT_FEMUR].push_back(Movement(90, 5.0f, delay, _inversed));
    movement[SEGMENT_COXA].push_back(Movement(90, 5.0f, delay, _inversed));

    movement[SEGMENT_TIBIA].push_back(Movement(135, 2.0f, delay, _inversed));
    movement[SEGMENT_FEMUR].push_back(Movement(80, 2.0f, delay, _inversed));
    movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, delay, _inversed));

    movement[SEGMENT_TIBIA].push_back(Movement(90, 2.0f, delay, _inversed));
    movement[SEGMENT_FEMUR].push_back(Movement(80, 2.0f, delay, _inversed));
    movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, delay, _inversed));
}