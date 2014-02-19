//#include "Arduino.h"
#include "HexaLeg.h"
#include "HexaLegSegment.h"
#include "TripodMovement.h"

//#define HEX_LEG_DEBUG

HexaLegSegment::HexaLegSegment(uint8_t _pin, int * valArray, bool digital, int degree) : moveStatus(false), speedMod(1.0f), isDigital(digital), pin(_pin)
{
    current_angle = 0;
    target_angle = 0;
    servo = new Servo();

    servo->attach(_pin, MIN_MICROS, MAX_MICROS, MIN_MICROS, MAX_MICROS);
    servo->write(degree); // init
}

HexaLeg::HexaLeg(uint8_t (*pins)[3], int * valArray, bool inversed)
{
    sequence = NULL;
    speedArr = valArray;
    legInversed = inversed;

    for (int i = 0; i < TOTAL_SEGMENTS; ++i)
    {
        segments[i] = NULL;
    }

    // Position after start
    int angles[3] =
    {
        90,  // SEGMENT_COXA
        30,  // SEGMENT_FEMUR
        120   // SEGMENT_TIBIA
        //inversed ? 60 : 120
    };

    for (uint8_t i = 0; i < TOTAL_SEGMENTS; ++i)
    {
        int arr = i * 4;

        uint16_t angle = angles[i];

        angle = Movement::calcAngle(angle, inversed);

        //char buf[255];
        //sprintf(buf, "Inversed: %u, segment: %s, angle: %u, result: %u", inversed, SegToText[i], angles[i], angle);
        //Serial.println(buf);

        segments[i] = new HexaLegSegment((pins[0][i]), &valArray[arr], false/*i == SEGMENT_COXA*/, angle);

            segments[i]->current_angle = map(angle, 0, 180, MIN_MICROS, MAX_MICROS);
            segments[i]->target_angle = map(angle, 0, 180, MIN_MICROS, MAX_MICROS);

        segments[i]->moveStatus = true;
        sequenceTimer[i] = 0;
    }
}

void HexaLeg::AddSequence(MovementSequence * vec)
{
    if (sequence != NULL)
    {
        delete sequence;
    }

    if (vec)
        vec->Init();
    sequence = vec;
        for (uint8_t i = 0; i < TOTAL_SEGMENTS; ++i)
    sequenceTimer[i] = 0;
}

void HexaLeg::UpdateServos()
{
    HexaLegSegment * servo;

    for (int i=0; i< TOTAL_SEGMENTS; ++i)
    {
         servo = segments[i];

        if (!servo || !sequence)
        {
            continue;

    Serial.println("no sequence");
        }

        if (servo->moveStatus == false)
        {
            if (sequenceTimer[i] >= millis())
                continue;

            if (!sequence->HasSequence(i))
                continue;

            const Movement * move = sequence->GetNextSequence(i);

            if (!move)
            {
                continue;
            }

#ifdef HEX_LEG_DEBUG
            Serial.print(SegToText[i]);
            Serial.print("\t");
            Serial.print(servo->target_angle);
            Serial.print(" angle ");
            Serial.print(move->angle);
            Serial.print("\t");
            Serial.println(move->speed);
#endif

            if (move->speed != 0)
                MoveSegmentDeg(i, move->angle, move->speed);

                if (segments[i]->isDigital)
                    segments[i]->reattach();
            sequenceTimer[i] = move->delay + millis();

            sequence->ClearTop(i);
            continue;
        }
        else
        {
            bool done = false;

            if (segments[i]->moveStatus == false)
            {
#ifdef HEX_LEG_DEBUG
                Serial.print(SegToText[i]);
                Serial.print(" is stopped.");
#endif
                continue;
            }

            if (abs(servo->current_angle - servo->target_angle) > 11.0f / 3 *  servo->speedMod)
            {
                int8_t direction = (servo->target_angle < servo->current_angle) ? -1 : 1;

                servo->current_angle += direction  * servo->speedMod;
                servo->move(servo->current_angle);

                if (!sequence->_infinite &&  abs(servo->current_angle - servo->target_angle) <= 11.0f / 3 * servo->speedMod)
                    done = true;
            }
            else if (!sequence->_infinite)
                done = true;

            if (done)
            {
                segments[i]->moveStatus = false;
                if (segments[i]->isDigital)
                    segments[i]->detach();

#ifdef HEX_LEG_DEBUG
                Serial.print(SegToText[i]);
                Serial.println(" done");
#endif
            }
        }
    }
}

void HexaLeg:: MoveSegment(uint8_t index, uint16_t angle, float speed, bool forced)
{
    if (segments[index]->moveStatus == false && !forced)
        return;

    segments[index]->target_angle = angle;
    segments[index]->speedMod = speed;
    segments[index]->moveStatus = true;
}

void HexaLeg:: MoveSegmentDeg(uint8_t index, uint16_t angle, float speed, bool forced)
{
    if (segments[index]->moveStatus == false && !forced)
        return;

    angle = map(angle, 0, 180, MIN_MICROS, MAX_MICROS);

    segments[index]->target_angle = angle;
    segments[index]->speedMod = speed;
    segments[index]->moveStatus = true;
}

void HexaLeg::StopSegment(uint8_t index)
{
    segments[index]->moveStatus = false;
}

void HexaLeg::SetTargetAngle(int index, int angle, bool inversed)
{
    segments[index]->target_angle = map(Movement::calcAngle(angle, inversed), 0, 180, MIN_MICROS, MAX_MICROS);
}