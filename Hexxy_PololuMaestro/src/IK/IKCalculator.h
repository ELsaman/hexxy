#ifndef IK_CALCULATOR_H
#define IK_CALCULATOR_H

//#include "Defines.h"
#include "Common.h"
#include <math.h>

#define sq(a) a * a

struct IKLegAngles
{
    float coxa;
    float femur;
    float tibia;

    float getAngle(int idx)
    {
        switch (idx)
        {
            case SEGMENT_COXA: return coxa;
            case SEGMENT_FEMUR: return femur;
            case SEGMENT_TIBIA: return tibia;
        }

        return 0.0f;
    }
};

struct IKBodyMods
{
    IKBodyMods() : rotX(0.0f), rotY(0.0f), rotZ(0.0f), posX(0), posY(0), heightMod(0) {}
    float rotX; // roll
    float rotY; // pitch
    float rotZ; // yaw (rotation)
    int posX;
    int posY;
    int heightMod;
};



class IKCalculator
{
public:

    static Position bodyIK(int X, int Y, int Z, LegOffset coxaOffset, IKBodyMods rot, float Zrotation = 0.0f)
    {
        Position ans;

        float cosB = cos(rot.rotX);
        float sinB = sin(rot.rotX);
        float cosG = cos(rot.rotY);
        float sinG = sin(rot.rotY);
        float cosA = cos(rot.rotZ + Zrotation);
        float sinA = sin(rot.rotZ + Zrotation);

        int totalX = X + coxaOffset.X + rot.posX;
        int totalY = Y + coxaOffset.Y + rot.posY;

        ans.x = totalX - int(totalX*cosG*cosA + totalY*sinB*sinG*cosA + Z*cosB*sinG*cosA - totalY*cosB*sinA + Z*sinB*sinA) + rot.posX;
        ans.y = totalY - int(totalX*cosG*sinA + totalY*sinB*sinG*sinA + Z*cosB*sinG*sinA + totalY*cosB*cosA - Z*sinB*cosA) + rot.posY;
        ans.z = Z - int(-totalX*sinG + totalY*sinB*cosG + Z*cosB*cosG);

        return ans;
    }

    static IKLegAngles legsIK(int X, int Y, int Z)
    {
        IKLegAngles ans;


        // first, make this a 2DOF problem... by solving coxa
        ans.coxa = (atan2(X, Y));
        long trueX = sqrt(sq((long)X) + sq((long)Y)) - LENGTH_COXA;
        long im = sqrt(sq((long)trueX) + sq((long)Z));    // length of imaginary leg

        // get femur angle above horizon...
        float q1 = -atan2(Z, trueX);
        long d1 = sq(LENGTH_FEMUR) - sq(LENGTH_TIBIA) + sq(im);
        long d2 = 2 * LENGTH_FEMUR*im;
        float q2 = acos((float)d1 / (float)d2);
        ans.femur = (q1 + q2);

        // and tibia angle from femur...
        d1 = sq(LENGTH_FEMUR) - sq(im) + sq(LENGTH_TIBIA);
        d2 = 2 * LENGTH_TIBIA*LENGTH_FEMUR;
        ans.tibia = (acos((float)d1 / (float)d2) - 1.57);

        //// first, make this a 2DOF problem... by solving coxa
        //ans.coxa = atan2(X, Y);
        ////ans.coxa = radToServo(atan2(X, Y));
        //long trueX = sqrt(sq(X) + sq(Y)) - LENGTH_COXA;
        //long im = sqrt(sq(trueX) + sq(Z));    // length of imaginary leg
        //
        //// get femur angle above horizon...
        //float q1 = -atan2(Z, trueX);
        //long d1 = sq(LENGTH_FEMUR) - sq(LENGTH_TIBIA) + sq(im);
        //long d2 = 2 * LENGTH_FEMUR*im;
        //float q2 = acos((float)d1 / (float)d2);
        //ans.femur = q1 + q2;
        ////ans.femur = radToServo(q1 + q2);
        //
        //// and tibia angle from femur...
        //d1 = sq(LENGTH_FEMUR) - sq(im) + sq(LENGTH_TIBIA);
        //d2 = 2 * LENGTH_TIBIA*LENGTH_FEMUR;
        //ans.tibia = acos((float)d1 / (float)d2) - 1.57;
        ////ans.tibia = radToServo(acos((float)d1 / (float)d2) - 1.57);

        return ans;
    }
};


#endif