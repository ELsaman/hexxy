#include "IKCalculator.h"

//#define COXA_X      94
//#define COXA_Y_N    55
//#define COXA_Y_M    80

//static const LegOffset coxaPos[LEG_COUNT] = 
//{
//    {+COXA_X    , +COXA_Y_N},  // LEG_RIGHT_FRONT
//    {0          , +COXA_Y_M},  // LEG_RIGHT_MIDDLE
//    {-COXA_X    , +COXA_Y_N},  // LEG_RIGHT_BACK
//    {+COXA_X    , -COXA_Y_N},  // LEG_LEFT_FRONT
//    {0          , -COXA_Y_M},  // LEG_LEFT_MIDDLE
//    {-COXA_X    , -COXA_Y_N}   // LEG_LEFT_BACK
//};
//
//Position IKCalculator::doBodyIK(LegIds legId, const IKBodyMods &rot, float Zrotation /* = 0.0f */)
//{
//    Position pos;
//
//    const LegOffset &offset = coxaPos[legId];
//
//    float cosB = cos(rot.rotX);
//    float sinB = sin(rot.rotX);
//    float cosG = cos(rot.rotY);
//    float sinG = sin(rot.rotY);
//    float cosA = cos(rot.rotZ + Zrotation);
//    float sinA = sin(rot.rotZ + Zrotation);
//
//    int totalX = offset.X;
//    int totalY = offset.Y;
//    int totalZ = 90;
//
//    pos.x = int(totalX*cosG*cosA + totalY*sinB*sinG*cosA + totalZ*cosB*sinG*cosA - totalY*cosB*sinA + totalZ*sinB*sinA);
//    pos.y = int(totalX*cosG*sinA + totalY*sinB*sinG*sinA + totalZ*cosB*sinG*sinA + totalY*cosB*cosA - totalZ*sinB*cosA);
//    pos.z = int(-totalX*sinG + totalY*sinB*cosG + totalZ*cosB*cosG);
//
//    return pos;
//}