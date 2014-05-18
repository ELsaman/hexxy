#ifndef COMMON_H
#define COMMON_H

#include "Arduino.h"

enum Defines
{
    LEG_COUNT       = 0,
};

enum Segments
{
    SEGMENT_COXA,
    SEGMENT_FEMUR,
    SEGMENT_TIBIA,
    SEGMENT_MAX
};

static const uint8_t legPins[LEG_COUNT][SEGMENT_MAX] = 
{
    { 0, 1, 2 },
    { 3, 4, 5 },
    { 6, 7, 8 },
    { 9, 10, 11 },
    { 12, 13, 14 },
    { 15, 16, 17 }
};

#endif