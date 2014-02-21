// 
// 
// 

#include "HexapodLeg.h"
#include "Defines.h"

HexapodLeg::HexapodLeg(uint8_t(*pins)[3], int * valArray, bool inversed) : _inversedLeg(inversed)
{
    for (int i = 0; i < TOTAL_SEGMENTS; ++i)
    {
        _segments[i] = SegmentServo(pins[0][i], DEFAULT_MIN_MICROS, DEFAULT_MAX_MICROS, 90);
        _sequenceTimer[i] = 0;
    }
}

void HexapodLeg::StopMovement(int8_t segment /* = -1 */)
{
    if (segment < 0)
    {
        for (int i = 0; i < TOTAL_SEGMENTS; ++i)
            _segments[i].StopMovement();
    } else if (segment < TOTAL_SEGMENTS)
        _segments[segment].StopMovement();
}

void HexapodLeg::AddSequence(MovementSequence * newSeq)
{
    if (newSeq == NULL)
        return;

    if (_sequence != NULL)
        delete _sequence;
    
    newSeq->Init();
    _sequence = newSeq;

    for (int i = 0; i < TOTAL_SEGMENTS; ++i)
        _sequenceTimer[i] = 0;
}

void HexapodLeg::UpdateSegments()
{
    if (!_sequence)
        return;

    SegmentServo * segment = NULL;

    for (int i = 0; i < TOTAL_SEGMENTS; ++i)
    {
        segment = &_segments[i];

        // Wait until we have to move
        if (!segment->IsMoving())
        {
            if (_sequenceTimer[i] >= millis())
                continue;

            if (!_sequence->HasSequence(i))
                continue;

            const Movement * move = _sequence->GetNextSequence(i);

            if (!move)
                continue;

            segment->StartMovement(move->angle, move->speed, _sequence->IsInfinite(), true);

            _sequenceTimer[i] = move->delay + millis();

            _sequence->ClearTop(i);

        } else
            segment->Update();
    }
}
