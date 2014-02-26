#include "MovementSequence.h"

struct TargetedMovement : public MovementSequence
{
    TargetedMovement(bool inversed, uint16_t angle) : MovementSequence(inversed, true)
    {
        _angle = angle;
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