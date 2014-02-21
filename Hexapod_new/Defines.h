#ifndef DEFINES_H
#define DEFINES_H

enum MoveStatus
{
    MOVE_STATUS_STOPPED,
    MOVE_STATUS_MOVING
};

enum Pulses
{
    DEFAULT_MIN_MICROS          = 550,
    DEFAULT_MAX_MICROS          = 2400
};

enum LegSegments
{
    SEGMENT_COXA,
    SEGMENT_FEMUR,
    SEGMENT_TIBIA,
    TOTAL_SEGMENTS
};

static const char* SegToText[TOTAL_SEGMENTS] =
{
    "SEGMENT_COXA",
    "SEGMENT_FEMUR",
    "SEGMENT_TIBIA",
};

#endif