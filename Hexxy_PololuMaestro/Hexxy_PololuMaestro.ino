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
#include "Util.h"

//#define XDIFF       0
//#define YDIFF       150
IKBodyMods oldMods = IKBodyMods();

#define XDIFF       -50
#define YDIFF       100
#define YDIFF_M       125

#define OFF_Y_N         55
#define OFF_Y_M         80
#define OFF_X           94
#define HEIGHT          90


// each leg's default position
static const Position END_POSITIONS[LEG_COUNT] = 
{
    { XDIFF,     YDIFF,     HEIGHT},  // LEG_RIGHT_FRONT
    { 0,         YDIFF_M,     HEIGHT},  // LEG_RIGHT_MIDDLE
    { -XDIFF,    YDIFF,     HEIGHT},  // LEG_RIGHT_BACK
    { XDIFF,    -YDIFF,     HEIGHT},  // LEG_LEFT_FRONT
    { 0,        -YDIFF_M,     HEIGHT},  // LEG_LEFT_MIDDLE
    { -XDIFF,   -YDIFF,     HEIGHT}   // LEG_LEFT_BACK
};


// Coxa offset from robot centre
static const LegOffset LEG_OFFSETS[LEG_COUNT] =
{
    { +OFF_X,   +OFF_Y_N},
    {      0,   +OFF_Y_M },
    { -OFF_X,   +OFF_Y_N},
    { +OFF_X,   -OFF_Y_N},
    {      0,   -OFF_Y_M},
    { -OFF_X,   -OFF_Y_N}
};

LegStep * fwdStep;
LegStep * revStep;


int oldX, oldY, oldZ = 1;
uint8_t positionBuffer[LEG_COUNT][SEGMENT_MAX] = { 0 };
uint8_t oldPosBuffer[LEG_COUNT][SEGMENT_MAX] = { 0 };
unsigned long updateTimer = 0;

void setup()
{
    Serial.begin(PC_SERIAL_BAUD);
    Serial3.begin(CONTROLLER_BAUD);
    //sSerialMgr.instance();

    //oldMods.rotZ = 10.0f;

    delay(3000);

    fwdStep = new LegStep(0);
    revStep = new LegStep(2);

    oldX = oldY = 0;
}



int tim = 0;

bool normalize(int &angle)
{
    if (angle <= 0 || angle >= 180)
        return true;
    return false;
}



int fwdPos[3] = { 0 };
int revPos[3] = { 0 };

void loop()
{

    if (updateTimer <= millis())
    {
        const InputState * state = sInputMgr.getCurrentState();
        const IKBodyMods * mods = sInputMgr.getCurrentState()->getRotation();

        // Simple tripod movement implementation
        // Use 2 steps generators
        fwdStep->Update();
        revStep->Update();
        fwdStep->GetCurrentPos(fwdPos);
        revStep->GetCurrentPos(revPos);

        //bool hasRotation = fabs(mods->rotX) > 0.0f || fabs(mods->rotY) > 0.0f || fabs(mods->rotZ) > 0.0f ;

        // Iterate through all leg and calculate positions. Send data to pololu if the coordinates changed
        //if (hasRotation)
        {
            bool reverse = false;

            for (uint8_t legNum = LEG_RIGHT_FRONT; legNum < LEG_COUNT; ++legNum)
            {
                // 1, 3, 5 on the same leg group
                int * pos = legNum % 2 ? revPos : fwdPos;
                DoKinematics((LegIds)legNum, pos[0], pos[1], pos[2], mods);
            }

            // send the data
            uint8_t val = 0;
            for (uint8_t legNum = LEG_RIGHT_FRONT; legNum < LEG_COUNT; ++legNum)
            {
                for (uint8_t seg = SEGMENT_COXA; seg < SEGMENT_MAX; ++seg)
                {

                    val = positionBuffer[legNum][seg];

                   //if (val >= 180 || val <=  0)
                   //    val = oldPosBuffer[legNum][seg];

                    if (val != oldPosBuffer[legNum][seg])
                    {
                        //if (legNum == 0 && seg == 0)
                            //DEBUG_LOG(LOG_TYPE_COMM, "Leg 1 coxa %d", val);
                        oldPosBuffer[legNum][seg] = val;
                        sPololuMgr.setServoValueSSC(legPins[legNum][seg], val);
                    }
                }
            }

        }
        updateTimer = millis() + UPDATE_TIMER;
    }

    // Process input commands etc
    //DEBUG_LOG(LOG_TYPE_MOVEMENT, "blabla");
    sSerialMgr.Update();
}

void DoKinematics(LegIds legNum, int StepX, int StepY, int StepZ, const IKBodyMods * bodyMods)
{
    int endX = END_POSITIONS[legNum].x;
    int endY = END_POSITIONS[legNum].y;
    int endZ = END_POSITIONS[legNum].z;


    int stepMod = 0;//;-int(float(abs(StepX)));

    switch (legNum)
    {
        case LEG_RIGHT_FRONT:
            StepX += stepMod;
            break;
        case LEG_RIGHT_MIDDLE:
            break;
        case LEG_RIGHT_BACK:
            StepX -= stepMod;
            break;
        case LEG_LEFT_FRONT:
            StepX += stepMod;
            break;
        case LEG_LEFT_MIDDLE:
            break;
        case LEG_LEFT_BACK:
            StepX -= stepMod;
            break;
    }

    float rotZ = 0.0f; // NYI

    // Calculate coxa position relative to body center (rotation matrix)
    Position body = IKCalculator::bodyIK(endX + StepX, endY + StepY, endZ + StepZ, LEG_OFFSETS[legNum], *bodyMods, rotZ);

    // Now change global (body) to local (leg) coordinates
    float localTransform = 0.0f;
    switch (legNum)
    {
        case LEG_RIGHT_FRONT:
            localTransform = 30.0f;
            endX = endX + body.x + StepX;
            endY = endY + body.y + StepY;
            endZ = endZ + body.z + StepZ;
            break;
        case LEG_RIGHT_MIDDLE:
            endX = endX + body.x + StepX;
            endY = endY + body.y + StepY;
            endZ = endZ + body.z + StepZ;
            //DEBUG_LOG(LOG_TYPE_COMM, "X: %d Y: %d Z: %d", en);
            break;
        case LEG_RIGHT_BACK:
            localTransform = 30.0f;
            endX = -endX - body.x - StepX;
            endY = endY + body.y + StepY;
            endZ = endZ + body.z + StepZ;
            break;
        case LEG_LEFT_FRONT:
            localTransform = 30.0f;
            endX = endX + body.x + StepX;
            endY = -endY - body.y - StepY;
            endZ = endZ + body.z + StepZ;
            break;
        case LEG_LEFT_MIDDLE:
            endX = endX + body.x + StepX;
            endY = -endY - body.y - StepY;
            endZ = endZ + body.z + StepZ;
            break;
        case LEG_LEFT_BACK:
            localTransform = 30.0f;
            endX = -endX - body.x - StepX;
            endY = -endY - body.y - StepY;
            endZ = endZ + body.z + StepZ;
            break;
    }
    //if (legNum == 0)
        //DEBUG_LOG(LOG_TYPE_COMM, "X: %d Y: %d Z: %d", 0, 0, StepZ);

    IKLegAngles angles = IKCalculator::legsIK(endX, endY, endZ);

    angles.coxa += localTransform * DEG_TO_RAD_F;
    angles.femur += HALF_PI_F;
    angles.tibia += HALF_PI_F;

    // Half pi = middle position
    switch (legNum)
    {
        case LEG_RIGHT_FRONT:
            angles.coxa = HALF_PI_F + angles.coxa;
            break;
        case LEG_RIGHT_MIDDLE:
            angles.coxa = HALF_PI_F + angles.coxa;
            break;
        case LEG_RIGHT_BACK:
            angles.coxa = HALF_PI_F - angles.coxa;
            break;
        case LEG_LEFT_FRONT:
            angles.coxa = HALF_PI_F - angles.coxa;
            break;
        case LEG_LEFT_MIDDLE:
            angles.coxa = HALF_PI_F - angles.coxa;
            break;
        case LEG_LEFT_BACK:
            angles.coxa = HALF_PI_F + angles.coxa;
            break;
    }

    // left side - correct femur angles (invert)
    if (legNum > LEG_RIGHT_BACK)
    {
        angles.femur = PI_F - angles.femur;
        angles.tibia = PI_F - angles.tibia;
    }

    // convert from radians to degrees
    for (uint8_t seg = SEGMENT_COXA; seg < SEGMENT_MAX; ++seg)
    {

        float angle = float(angles.getAngle(seg) * RAD_TO_DEG_F);

        // normalize the angle if the value is out of bounds (0 - 180)
        if (angle > 180.0f)
        {
            DEBUG_LOG(LOG_TYPE_MOVEMENT, "Angle larger than 180 deg (%d) for Leg: %u (%s), Segment %u (%s)", (int)angle, (uint8_t)legNum, legNames[(uint8_t)legNum], seg, segmentNames[seg]);
            angle = 180.0f;
        } else if (angle < 0.0f)
        {
            DEBUG_LOG(LOG_TYPE_MOVEMENT, "Angle smaller than 0 deg (%d) for Leg: %u (%s), Segment %u (%s)", (int)angle, (uint8_t)legNum, legNames[(uint8_t)legNum], seg, segmentNames[seg]);
            angle = 0.0f;
        }

        // convert to values accepted by Pololu (SSC Protocol: 0-255 range)
        positionBuffer[legNum][seg] = uint8_t(map((long)angle, 0, 180, 0, 255));
    }
}