#include "MovementSequence.h"

struct TargetedMovement : public MovementSequence
{
    TargetedMovement(uint16_t angle_coxa = 60, uint16_t angle_femur = 60, uint16_t angle_tibia = 60) : MovementSequence(false, true)
    {
        _angles[SEGMENT_COXA] = angle_coxa;
        _angles[SEGMENT_FEMUR] = angle_femur;
        _angles[SEGMENT_TIBIA] = angle_tibia;
    }

    void Init()
    {
        movement[SEGMENT_TIBIA].push_back(Movement(_angles[SEGMENT_TIBIA], 3.0f, 5000, IsInversed()));
        movement[SEGMENT_FEMUR].push_back(Movement(_angles[SEGMENT_FEMUR], 3.0f, 5000, IsInversed()));
        movement[SEGMENT_COXA].push_back(Movement(_angles[SEGMENT_COXA], 3.0f, 5000, false));
    };
private:
    uint16_t _angles[TOTAL_SEGMENTS];
};

struct StretchMovement : public MovementSequence
{
    StretchMovement(uint8_t id) : MovementSequence(false, false)
    {
        _id = id;
    }

    void Init()
    {
        uint8_t coxaAngles[6] =
        {
            130,
            90,
            50,
            50,
            90,
            130
        };

        movement[SEGMENT_TIBIA].push_back(Movement(20, 3.0f, 5000, IsInversed()));
        movement[SEGMENT_FEMUR].push_back(Movement(180, 3.0f, 5000, IsInversed()));
        movement[SEGMENT_COXA].push_back(Movement(coxaAngles[_id], 3.0f, 5000, false));

        //_inversed = false;

        int timer1 = 1000;
        int timer2 = 3000;

        // Put both on the ground

        movement[SEGMENT_TIBIA].push_back(Movement(80, 5.0f, _id % 2 ? 4000 : 3000, IsInversed()));
        movement[SEGMENT_FEMUR].push_back(Movement(100, 2.0f, _id % 2 ? 4000 : 3000, IsInversed()));

        for (int i = 0; i < 6; ++i)
        {
            if (_id % 2)
            {
                //First one to go up

                //UP
                movement[SEGMENT_TIBIA].push_back(Movement(50, 3.0f, 2000, IsInversed()));
                movement[SEGMENT_FEMUR].push_back(Movement(150, 5.0f, 2000, IsInversed()));


                //DOWN
                movement[SEGMENT_TIBIA].push_back(Movement(80, 5.0f, 4000, IsInversed()));
                movement[SEGMENT_FEMUR].push_back(Movement(100, 3.0f, 4000, IsInversed()));

            } else
            {
                // up first (2)


                //DOWN
                movement[SEGMENT_TIBIA].push_back(Movement(80, 5.0f, 4000, IsInversed()));
                movement[SEGMENT_FEMUR].push_back(Movement(100, 3.0f, 4000, IsInversed()));


                //UP
                movement[SEGMENT_TIBIA].push_back(Movement(50, 3.0f, 2000, IsInversed()));
                movement[SEGMENT_FEMUR].push_back(Movement(150, 5.0f, 2000, IsInversed()));

            }
        }
    };
private:
    uint8_t _id;
};