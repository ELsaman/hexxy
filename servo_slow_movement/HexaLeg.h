#ifndef HEXA_LEG
#define HEXA_LEG

#include "HexaLegSegment.h"
#include "MovementSequence.h"

//#include "Arduino.h"

#define SPEED_STOP 1.0f

enum
{
    DEFAULT_SPEED       = 11, // average 11 µS width per 1°
    PULSE_DELAY
};

class HexaLeg
{
public:
    HexaLeg(uint8_t (*pins)[3], int * valArray, bool inversed);

    void UpdateServos();

    void MoveSegment(uint8_t index, uint16_t angle, float speed = 1.0f, bool forced = true);
    void MoveSegmentDeg(uint8_t index, uint16_t angle, float speed = 1.0f, bool forced = true);
    void StopSegment(uint8_t index);

    void AddSequence(MovementSequence * vec);
    bool legInversed;

    void SetTargetAngle(int index, int angle, bool inversed);

private:
    MovementSequence * sequence;
    HexaLegSegment * segments[TOTAL_SEGMENTS];
    uint64_t sequenceTimer[TOTAL_SEGMENTS];
    int * speedArr;
};

#endif