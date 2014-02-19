#include "MovementSequence.h"
#include "Arduino.h"

MovementSequence::MovementSequence(bool inversed, bool infinite)
{
    //Serial.println("MovementSequence reset");
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
    movement[SEGMENT_TIBIA].push_back(Movement(90, 0.3f, 0, _inversed));
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
    }
}

void DebugResetMovement::Init()
{
    Serial.println("DebugResetMovement init");
    //float speed = 1.0f;

    


    //movement[SEGMENT_TIBIA].push_back(Movement(40, 2.0f, 8000, _inversed));
    //movement[SEGMENT_FEMUR].push_back(Movement(150, 2.0f, 8000, _inversed));
    //movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, 8000, _inversed));
    //
    //movement[SEGMENT_TIBIA].push_back(Movement(40, 2.0f, 8000, _inversed));
    //movement[SEGMENT_FEMUR].push_back(Movement(150, 2.0f, 8000, _inversed));
    //movement[SEGMENT_COXA].push_back(Movement(60, 2.0f, 8000, _inversed));
    //
    //movement[SEGMENT_TIBIA].push_back(Movement(40, 2.0f, 8000, _inversed));
    //movement[SEGMENT_FEMUR].push_back(Movement(150, 2.0f, 8000, _inversed));
    //movement[SEGMENT_COXA].push_back(Movement(120, 2.0f, 8000, _inversed));
    //
    //movement[SEGMENT_TIBIA].push_back(Movement(40, 2.0f, 8000, _inversed));
    //movement[SEGMENT_FEMUR].push_back(Movement(150, 2.0f, 8000, _inversed));
    //movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, 8000, _inversed));

    int delay = 8000;

    delay = 300000;

    movement[SEGMENT_TIBIA].push_back(Movement(90, 5.0f, delay, _inversed));
    movement[SEGMENT_FEMUR].push_back(Movement(90, 5.0f, delay, _inversed));
    movement[SEGMENT_COXA].push_back(Movement(90, 5.0f, delay, _inversed));
    //return;

    movement[SEGMENT_TIBIA].push_back(Movement(135, 2.0f, delay, _inversed));
    movement[SEGMENT_FEMUR].push_back(Movement(80, 2.0f, delay, _inversed));
    movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, delay, _inversed));

    movement[SEGMENT_TIBIA].push_back(Movement(90, 2.0f, delay, _inversed));
    movement[SEGMENT_FEMUR].push_back(Movement(80, 2.0f, delay, _inversed));
    movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, delay, _inversed));

    //movement[SEGMENT_TIBIA].push_back(Movement(120, 2.0f, 8000, _inversed));
    //movement[SEGMENT_FEMUR].push_back(Movement(60, 2.0f, 8000, _inversed));
    //movement[SEGMENT_COXA].push_back(Movement(90, 2.0f, 8000, _inversed));

    //movement[SEGMENT_TIBIA].push_back(Movement(90, 1.0f, 2000, _inversed));
    //movement[SEGMENT_FEMUR].push_back(Movement(90, 1.0f, 2000, _inversed));
    //movement[SEGMENT_COXA].push_back(Movement(90, 1.0f, 2000, _inversed));

    //bool inversed = _inversed;
    //    movement[SEGMENT_FEMUR].push_back(Movement(150, 2.0f, 5000, inversed));
    //    movement[SEGMENT_FEMUR].push_back(Movement(120, 2.0f, 5000, inversed));
    //    movement[SEGMENT_FEMUR].push_back(Movement(60, 2.0f, 5000, inversed));
    //    movement[SEGMENT_FEMUR].push_back(Movement(90, 2.0f, 5000, inversed));

    //int delay = 0;
    //float speed = 3.0f;
    //for (int i = 0; i < 8; ++i)
    //{
    //    movement[SEGMENT_COXA].push_back(Movement(150, speed * i/2, delay));
    //    //movement[SEGMENT_FEMUR].push_back(Movement(150, speed, delay));
    //    //movement[SEGMENT_COXA]. push_back(Movement(150, speed, delay));
    //
    //    movement[SEGMENT_COXA].push_back(Movement(30, speed * i/2, delay));
    //    //movement[SEGMENT_FEMUR].push_back(Movement(30, speed, delay));
    //    //movement[SEGMENT_COXA]. push_back(Movement(30, speed, delay));
    //}
}