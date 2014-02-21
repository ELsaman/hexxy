// HexapodLeg.h

#ifndef _HEXAPODLEG_h
#define _HEXAPODLEG_h

#include "MovementSequence.h"
#include "SegmentServo.h"

class HexapodLeg
{
public:
    HexapodLeg(uint8_t(*pins)[3], int * valArray, bool inversed);

    void UpdateSegments();
    void StopMovement(int8_t segment = -1);

    void AddSequence(MovementSequence * sequence);

private:
    SegmentServo _segments[TOTAL_SEGMENTS];
    bool _inversedLeg;
    uint64_t _sequenceTimer[TOTAL_SEGMENTS];
    MovementSequence * _sequence;
};

#endif

