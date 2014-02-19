//
//
//

#include "TripodMovement.h"

struct ResetMovement : public MovementSequence
{
    void Init()
    {
        //Serial.println("initial");
        movement[0].push_back(Movement(15, 1.0f, 0));
        movement[1].push_back(Movement(60, 1.0f, 0));
        movement[2].push_back(Movement(90, 1.0f, 0));
    }
};