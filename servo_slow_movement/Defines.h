#ifndef DEFINES_H
#define DEFINES_H

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
