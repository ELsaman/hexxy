#include "Gait.h"

enum
{
    TRIPOD_GAIT_STEPS       = 3
};

class TripodGait : public Gait
{
    TripodGait() : Gait(TRIPOD_GAIT_STEPS, 1.0f) {}


};