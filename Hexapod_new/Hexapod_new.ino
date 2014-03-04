

#include "Hexxy.h"
#include "TargetedMovement.h"

//#include "Hexapod.h"
//#include "HexapodLeg.h"
#include <StandardCplusplus.h>
//#include "Movement.h"
//#include "MovementSequence.h"
//#include "SegmentServo.h"
#include <ServoNew.h>

Hexxy * hexxy;

unsigned long oldTime = 2L;
unsigned long timeMS = 2L;

void setup()
{
    Serial.begin(115200);
    hexxy = new Hexxy();


    hexxy->Init();
    uint8_t angles[6] = 
    {
        150,
        90,
        30,
        30,
        90,
        150,
    };

    for (uint8_t i = 0; i < LEG_COUNT; ++i)
    {
        //MovementSequence * seq = new TargetedMovement(angles[i], 180, 20);
        MovementSequence * seq = new StretchMovement(i);
        hexxy->AddSequence(i, seq);
    }

    delay(200);
    oldTime = micros();
}


void loop()
{
    timeMS = micros();
    if (timeMS > oldTime)
    {
        hexxy->UpdateLegs();
        oldTime = micros() + 5000;
    }
    
    if (Serial.available())
        ReceiveSerial();
}

int oldAngles[3] = {90, 90, 90};
int tarAngles[3] = {90, 90, 90};
char buf2[5];

void ReceiveSerial()
{
    int tgt[3] = {0, 0, 0};

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 5; ++j)
            buf2[j] = 0;

        size_t size = Serial.readBytesUntil(' ', buf2, 5);
        char temp[5];
        for (int j = 0; j <= size; ++j)
            temp[j] = buf2[j];
        tgt[i] = atoi(temp);
    }

    for (int i=0; i< LEG_COUNT; ++i)
    {
        bool inv = i > 2;

        hexxy->AddSequence(i, new TargetedMovement(tgt[SEGMENT_COXA], tgt[SEGMENT_FEMUR], tgt[SEGMENT_TIBIA]));
        //legs[i]->SetTargetAngle(SEGMENT_COXA, tgt[SEGMENT_COXA], false);
        //legs[i]->SetTargetAngle(SEGMENT_FEMUR, tgt[SEGMENT_FEMUR], inv);
        //legs[i]->SetTargetAngle(SEGMENT_TIBIA, tgt[SEGMENT_TIBIA], inv);
    }

    while (Serial.available())
        Serial.read();
}
