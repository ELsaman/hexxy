#include <utility.h>
#include <StandardCplusplus.h>
#include <SoftwareSerial.h>
#include "SerialMgr.h"
#include "IKCalculator.h"
#include "InputMgr.h"
#include "PololuMgr.h"
#include "Common.h"
#include "Defines.h"
#include "Step.h"

#define PC_SERIAL_BAUD      38400

//#define XDIFF       0
//#define YDIFF       150
IKBodyMods oldMods = IKBodyMods();

#define XDIFF       0
#define YDIFF       100

#define OFF_Y_N         55
#define OFF_Y_M         OFF_Y_N + 25
#define OFF_X           94
#define HEIGHT          90


// each leg's default position
static const Position endp[LEG_COUNT] = 
{
    { XDIFF,     YDIFF,     HEIGHT},  // LEG_RIGHT_FRONT
    { 0,         YDIFF,     HEIGHT},  // LEG_RIGHT_MIDDLE
    { -XDIFF,     YDIFF,     HEIGHT},  // LEG_RIGHT_BACK
    { XDIFF,    -YDIFF,     HEIGHT},  // LEG_LEFT_FRONT
    { 0,        -YDIFF,     HEIGHT},  // LEG_LEFT_MIDDLE
    { -XDIFF,    -YDIFF,     HEIGHT}   // LEG_LEFT_BACK
};


// Coxa offset from robot centre
static const LegOffset legOffsets[LEG_COUNT] =
{
    { +OFF_X,   +OFF_Y_N},
    {      0,   +OFF_Y_N + 25},
    { -OFF_X,   +OFF_Y_N},
    { +OFF_X,   -OFF_Y_N},
    {      0,   -OFF_Y_N - 25},
    { -OFF_X,   -OFF_Y_N}
};

LegStep * step;
LegStep * stepRev;
void setup()
{

  /* add setup code here */
    Serial.begin(PC_SERIAL_BAUD);
  
  oldMods.rotZ = 10.0f;

  delay(1000);
  
  step = new LegStep();
  stepRev = new LegStep(2);
}

long updateTimer = 0;



int tim = 0;

bool normalize(int &angle)
{
    if (angle <= 0 || angle >= 180)
        return true;
    return false;
}

float oldX, oldY, oldZ;

void loop()
{

    if (updateTimer <= millis())
    {
            IKBodyMods mods = sInputMgr.getCurrentState()->getRotation();
            
            step->Update();
            stepRev->Update();
            int x, y, z;
            step->GetCurrentPos(x, y, z);
            int x1, y1, z1;
            stepRev->GetCurrentPos(x1, y1, z1);

            //if (mods.rotZ != oldMods.rotZ)
            if (oldX != x || oldY != y || oldZ != z)
            {

                //Serial.println();
                for (int i = 0; i < LEG_COUNT; ++i)
                {
                    oldMods = mods;
                    IKBodyMods mods2 = mods;
                    Position body;
                    IKLegAngles angles;

                    //mods2.rotZ = mods.rotZ;
                    //mods2.rotY = mods.rotZ;
                    //mods2.rotX = mods.rotZ;
                    //mods2.posY = 50;
                    float rotZ = 0; // *DEG_TO_RAD;

                    bool rev = i % 2;
                    int stepX = rev ? x : x1;
                    int stepY = rev ? y : y1;
                    int stepZ = rev ? z : z1;


                    //stepX = 0;
                    //stepY = 0;
                    //stepZ = 0;

                    int endX = endp[i].x;
                    int endY = endp[i].y;
                    int endZ = endp[i].z;
                    
                    body = IKCalculator::bodyIK(endX + stepX, endY + stepX, endZ + stepZ, legOffsets[i], mods2, rotZ);

                    float localTransform = 0.0f;

                    switch (i)
                    {
                        case LEG_RIGHT_FRONT:
                            localTransform = -30.0f;
                            endX = endX + body.x + stepX;
                            endY = endY + body.y + stepY;
                            endZ = endZ + body.z + stepZ;
                            break;
                        case LEG_RIGHT_MIDDLE:
                            endX = endX + body.x + stepX;
                            endY = endY + body.y + stepY;
                            endZ = endZ + body.z + stepZ;
                            break;
                        case LEG_RIGHT_BACK:
                            localTransform = 30.0f;
                            endX = -endX - body.x - stepX;
                            endY = endY + body.y + stepY;
                            endZ = endZ + body.z + stepZ;
                            break;
                        case LEG_LEFT_FRONT:
                            localTransform = 30.0f;
                            endX = endX + body.x + stepX;
                            endY = -endY - body.y - stepY;
                            endZ = endZ + body.z + stepZ;
                            break;
                        case LEG_LEFT_MIDDLE:
                            endX = endX + body.x + stepX;
                            endY = -endY - body.y - stepY;
                            endZ = endZ + body.z + stepZ;
                            break;
                        case LEG_LEFT_BACK:
                            localTransform = -30.0f;
                            endX = -endX - body.x - stepX;
                            endY = -endY - body.y - stepY;
                            endZ = endZ + body.z + stepZ;
                            break;
                    }

                    
                    //if (localTransform)
                    //{
                    //    localTransform *= DEG_TO_RAD;
                    //    double cosA = cos(localTransform);
                    //    double sinA = sin(localTransform);
                    //    //DEBUG_LOG(LOG_TYPE_COMM, "before X: %d, Y: %d, Z: %d", endX, endY, endZ);
                    //
                    //    endX = endY * cosA + endX * sinA;
                    //    endY = endX * cosA - endY * sinA;
                    //    //DEBUG_LOG(LOG_TYPE_COMM, "after X: %d, Y: %d, Z: %d", endX, endY, endZ);
                    //}

                    angles = IKCalculator::legsIK(endX, endY, endZ);

                    //angles.coxa += HALF_PI;
                    angles.femur += HALF_PI;
                    angles.tibia += HALF_PI;

                    // Half pi = middle position
                    switch (i)
                    {
                        case LEG_RIGHT_FRONT:
                            angles.coxa = HALF_PI + angles.coxa;
                            break;
                        case LEG_RIGHT_MIDDLE:
                            angles.coxa = HALF_PI + angles.coxa;
                            break;
                        case LEG_RIGHT_BACK:
                            angles.coxa = HALF_PI - angles.coxa;
                            break;
                        case LEG_LEFT_FRONT:
                            angles.coxa = HALF_PI - angles.coxa;
                            break;
                        case LEG_LEFT_MIDDLE:
                            angles.coxa = HALF_PI - angles.coxa;
                            break;
                        case LEG_LEFT_BACK:
                            angles.coxa = HALF_PI + angles.coxa;
                            break;
                    }
                    
                    if (i > 2)
                    {
                        //angles.coxa = M_PI - angles.coxa;
                        angles.femur = M_PI - angles.femur;
                        
                        if (i != 5)
                            angles.tibia = M_PI - angles.tibia;
                    }



                    int coxa = static_cast<float>(RAD_TO_DEG)* angles.coxa;
                    int femur = static_cast<float>(RAD_TO_DEG)* angles.femur;
                    int tibia = static_cast<float>(RAD_TO_DEG)* angles.tibia;
                    
                    if (normalize(coxa))
                        break;
                    if (normalize(femur))
                        break;
                    if (normalize(tibia))
                        break;

                    //DEBUG_LOG(LOG_TYPE_COMM, "Step %d Leg %u Position: x %d, y %d, z %d", stepX, i, endX, endY, endZ);
                    //DEBUG_LOG(LOG_TYPE_COMM, "Coxa %u Position: x %d, y %d, z %d", i, body.x, body.y, body.z);
                    //DEBUG_LOG(LOG_TYPE_COMM, "Leg %u Angles: Coxa: %d, Femur: %d, Tibia: %d", i, coxa, femur, tibia);

                    int coxaVal = map(coxa, 0, 180, 0, 255);
                    int femurVal = map(femur, 0, 180, 0, 255);
                    int tibiaVal = map(tibia, 0, 180, 0, 255);

                    
                    //if (i == 1)
                    //    femurVal = 254;
                    //else if (i == 4)
                    //    femurVal = 0;

                    sPololuMgr.setServoValueSSC(legPins[i][SEGMENT_COXA], coxaVal);
                    sPololuMgr.setServoValueSSC(legPins[i][SEGMENT_FEMUR], femurVal);
                    sPololuMgr.setServoValueSSC(legPins[i][SEGMENT_TIBIA], tibiaVal);

                    //Serial.println();
                }
            }

            //step->Update();
            //int x, y, z;
            //step->GetCurrentPos(x, y, z);
            //DEBUG_LOG(LOG_TYPE_COMM, "%u Position: x %d, y %d, z %d", step->tickCnt, x, y, z);
        //Serial.println();
            updateTimer = millis() + 20;
    }
        sSerialMgr.Update();

}
