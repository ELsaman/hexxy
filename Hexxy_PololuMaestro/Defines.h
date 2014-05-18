#ifndef DEFINES_H
#define DEFINES_H

#include "Util.h"

#define OFFSET_Y    9.5f
#define OFFSET_X_1  8
#define OFFSET_X_2  5.5f
#define LEG_COUNT   6

#define LENGTH_COXA     35 // coxa -> femur
#define LENGTH_FEMUR    100
#define LENGTH_TIBIA    125

struct LegOffset
{
    int X;
    int Y;
};

static const LegOffset legOffsets[LEG_COUNT] =
{
    { -OFFSET_X_2,  +OFFSET_Y   },
    { -OFFSET_X_1,  0           },
    { -OFFSET_X_2,  -OFFSET_Y   },
    { +OFFSET_X_2,  +OFFSET_Y   },
    { +OFFSET_X_1,  0           },
    { +OFFSET_X_2,  -OFFSET_Y   }
};

#endif