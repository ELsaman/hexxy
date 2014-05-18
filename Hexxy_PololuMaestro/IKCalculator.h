#ifndef IK_CALCULATOR_H
#define IK_CALCULATOR_H

#include "Defines.h"
#include <math.h>

#define sq(a) a * a

struct IKLegAngles
{
    float coxa;
    float femur;
    float tibia;
};

struct IKLegPosition
{
    int x;
    int y;
    int z;
};

struct IKBodyMods
{
    float rotX; // pitch
    float rotY; // yaw
    float rotZ; // roll
    int posX;
    int posY;
};
class IKCalculator
{
    static IKLegPosition calcBodyIK(int X, int Y, int Z, LegOffset leg, float legRot)
    {

        IKBodyMods rot = {0.0f, 0.0f, 0.0f, 0, 0};

        float cosB = cos(rot.rotX);
        float sinB = sin(rot.rotX);
        float cosG = cos(rot.rotY);
        float sinG = sin(rot.rotY);
        float cosA = cos(rot.rotZ + legRot);
        float sinA = sin(rot.rotZ + legRot);

        int totalX = X + leg.X + rot.posX;
        int totalY = Y + leg.Y + rot.posY;

        IKLegPosition ans;
        ans.x = totalX - int(totalX*cosG*cosA + totalY*sinB*sinG*cosA + Z*cosB*sinG*cosA - totalY*cosB*sinA + Z*sinB*sinA) + rot.posX;
        ans.y = totalY - int(totalX*cosG*sinA + totalY*sinB*sinG*sinA + Z*cosB*sinG*sinA + totalY*cosB*cosA - Z*sinB*cosA) + rot.posY;
        ans.z = Z - int(-totalX*sinG + totalY*sinB*cosG + Z*cosB*cosG);

        return ans;
    }

    static IKLegAngles legIK(int X, int Y, int Z)
    {
        IKLegAngles ans;

        // first, make this a 2DOF problem... by solving coxa
        ans.coxa = atan2(X, Y);
        long trueX = sqrt(sq((long)X) + sq((long)Y)) - LENGTH_COXA;
        long im = sqrt(sq((long)trueX) + sq((long)Z));    // length of imaginary leg

        // get femur angle above horizon...
        float q1 = -atan2(Z, trueX);
        long d1 = sq(LENGTH_FEMUR) - sq(LENGTH_TIBIA) + sq(im);
        long d2 = 2 * LENGTH_FEMUR*im;
        float q2 = acos((float)d1 / (float)d2);
        ans.femur = q1 + q2;

        // and tibia angle from femur...
        d1 = sq(LENGTH_FEMUR) - sq(im) + sq(LENGTH_TIBIA);
        d2 = 2 * LENGTH_TIBIA*LENGTH_FEMUR;
        ans.tibia = acos((float)d1 / (float)d2) - 1.57f;

        return ans;
    }
};


#endif