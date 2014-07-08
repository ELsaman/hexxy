#ifndef COMMON_H
#define COMMON_H


#define UPDATE_TIMER        20

#define LEG_COUNT   6

#define LENGTH_COXA     35 // coxa -> femur
#define LENGTH_FEMUR    100
#define LENGTH_TIBIA    150

enum Segments
{
    SEGMENT_COXA,
    SEGMENT_FEMUR,
    SEGMENT_TIBIA,
    SEGMENT_MAX
};

enum LegIds
{
    LEG_RIGHT_FRONT,
    LEG_RIGHT_MIDDLE,
    LEG_RIGHT_BACK,
    LEG_LEFT_FRONT,
    LEG_LEFT_MIDDLE,
    LEG_LEFT_BACK
};


struct Position
{
    int x;
    int y;
    int z;
};

struct LegOffset
{
    int X;
    int Y;
};



#endif