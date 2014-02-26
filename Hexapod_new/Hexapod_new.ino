

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

    hexxy = new Hexxy();

    hexxy->Init();
    for (uint8_t i = 0; i < LEG_COUNT; ++i)
    {
        MovementSequence * seq = new TargetedMovement(false, (uint16_t)90);
        hexxy->AddSequence(i, seq);
    }

    delay(2000);
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

}
