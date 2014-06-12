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

    //static Position calcBodyIK(int X, int Y, int Z, LegOffset leg, float legRot, IKBodyMods rot)
    //{              
    //    float cosRotX = cos(rot.rotX);
    //    float sinRotX = sin(rot.rotX);
    //    float cosRotY = cos(rot.rotY);
    //    float sinRotY = sin(rot.rotY);
    //    float cosRotZ = cos(rot.rotZ + legRot);
    //    float sinRotZ = sin(rot.rotZ + legRot);
    //
    //    int totalX = X + leg.X + rot.posX;
    //    int totalY = Y + leg.Y + rot.posY;
    //
    //    Position ans;
    //    ans.x = totalX - int(totalX*cosRotY*cosRotZ + totalY*sinRotX*sinRotY*cosRotZ + Z*cosRotX*sinRotY*cosRotZ - totalY*cosRotX*sinRotZ + Z*sinRotX*sinRotZ) + rot.posX;
    //    ans.y = totalY - int(totalX*cosRotY*sinRotZ + totalY*sinRotX*sinRotY*sinRotZ + Z*cosRotX*sinRotY*sinRotZ + totalY*cosRotX*cosRotZ - Z*sinRotX*cosRotZ) + rot.posY;
    //    ans.z =      Z - int(-totalX*sinRotY + totalY*sinRotX*cosRotY + Z*cosRotX*cosRotY);
    //
    //    return ans;
    //}
    //
    //static Position bodyIK2(int X, int Y, int Z, LegOffset leg, float legRot, IKBodyMods rot)
    //{
    //
    //    Position legPos[LEG_COUNT];
    //
    //    float cosRotX = cos(rot.rotX);
    //    float sinRotX = sin(rot.rotX);
    //    float cosRotY = cos(rot.rotY);
    //    float sinRotY = sin(rot.rotY);
    //    float cosRotZ = cos(rot.rotZ + legRot);
    //    float sinRotZ = sin(rot.rotZ + legRot);
    //
    //    //int totalX = X + leg.X + rot.posX;
    //    //int totalY = Y + leg.Y + rot.posY;
    //
    //    int totalX, totalY, totalZ;
    //
    //    int bodyRotOffsetX[6], bodyRotOffsetY[6], bodyRotOffsetZ[6];
    //    int tempFootPosX[6], tempFootPosY[6], tempFootPosZ[6];
    //
    //    for (int legNum = 0; legNum < 6; legNum++)
    //    {
    //        //Serial.print ("footPosCalc() Leg: "); Serial.println (legNum+1);
    //
    //        //sinRotZ = sin(radians(leg[legNum].bodyRotZ - commanderInput.bodyRotZ));
    //        //cosRotZ = cos(radians(leg[legNum].bodyRotZ - commanderInput.bodyRotZ));
    //
    //        totalX = endp[legNum].x ; //+ leg[legNum].legBasePos.x;
    //        totalY = endp[legNum].y ; //+ leg[legNum].legBasePos.y;
    //        totalZ = endp[legNum].z ; //+ leg[legNum].legBasePos.z;
    //
    //        bodyRotOffsetX[legNum] = round((totalY*cosRotY*sinRotZ + totalY*cosRotZ*sinRotX*sinRotY + totalX*cosRotZ*cosRotY - totalX*sinRotZ*sinRotX*sinRotY - totalZ*cosRotX*sinRotY) - totalX);
    //        bodyRotOffsetY[legNum] = round(totalY*cosRotX*cosRotZ - totalX*cosRotX*sinRotZ + totalZ*sinRotX - totalY);
    //        bodyRotOffsetZ[legNum] = round((totalY*sinRotZ*sinRotY - totalY*cosRotZ*cosRotY*sinRotX + totalX*cosRotZ*sinRotY + totalX*cosRotY*sinRotZ*sinRotX + totalZ*cosRotX*cosRotY) - totalZ);
    //
    //        // Calculated foot positions to acheive xlation/rotation input. Not coxa mounting angle corrected
    //        tempFootPosX[legNum] = endp[legNum].x + bodyRotOffsetX[legNum] - rot.posX + legOffsets[legNum].X;
    //        tempFootPosY[legNum] = endp[legNum].y + bodyRotOffsetY[legNum] - rot.posY + legOffsets[legNum].Y;
    //        tempFootPosZ[legNum] = endp[legNum].z + bodyRotOffsetZ[legNum] - 50;//rot.bodyTransZ + 50;
    //    }

#define COXA_ANGLE 60

    //    // Rotates X,Y about coxa to compensate for coxa mounting angles.
    //    legPos[0].x = round(tempFootPosY[0] * cos(radians(COXA_ANGLE)) - tempFootPosX[0] * sin(radians(COXA_ANGLE)));
    //    legPos[0].y = round(tempFootPosY[0] * sin(radians(COXA_ANGLE)) + tempFootPosX[0] * cos(radians(COXA_ANGLE)));
    //    legPos[0].z = tempFootPosZ[0];
    //    legPos[1].x = round(tempFootPosY[1] * cos(radians(COXA_ANGLE * 2)) - tempFootPosX[1] * sin(radians(COXA_ANGLE * 2)));
    //    legPos[1].y = round(tempFootPosY[1] * sin(radians(COXA_ANGLE * 2)) + tempFootPosX[1] * cos(radians(COXA_ANGLE * 2)));
    //    legPos[1].z = tempFootPosZ[1];
    //    legPos[2].x = round(tempFootPosY[2] * cos(radians(COXA_ANGLE * 3)) - tempFootPosX[2] * sin(radians(COXA_ANGLE * 3)));
    //    legPos[2].y = round(tempFootPosY[2] * sin(radians(COXA_ANGLE * 3)) + tempFootPosX[2] * cos(radians(COXA_ANGLE * 3)));
    //    legPos[2].z = tempFootPosZ[2];
    //    legPos[3].x = round(tempFootPosY[3] * cos(radians(COXA_ANGLE * 5)) - tempFootPosX[3] * sin(radians(COXA_ANGLE * 5)));
    //    legPos[3].y = round(tempFootPosY[3] * sin(radians(COXA_ANGLE * 5)) + tempFootPosX[3] * cos(radians(COXA_ANGLE * 5)));
    //    legPos[3].z = tempFootPosZ[3];
    //    legPos[4].x = round(tempFootPosY[4] * cos(radians(COXA_ANGLE * 6)) - tempFootPosX[4] * sin(radians(COXA_ANGLE * 6)));
    //    legPos[4].y = round(tempFootPosY[4] * sin(radians(COXA_ANGLE * 6)) + tempFootPosX[4] * cos(radians(COXA_ANGLE * 6)));
    //    legPos[4].z = tempFootPosZ[4];
    //    legPos[5].x = round(tempFootPosY[5] * cos(radians(COXA_ANGLE * 7)) - tempFootPosX[5] * sin(radians(COXA_ANGLE * 7)));
    //    legPos[5].y = round(tempFootPosY[5] * sin(radians(COXA_ANGLE * 7)) + tempFootPosX[5] * cos(radians(COXA_ANGLE * 7)));
    //    legPos[5].z = tempFootPosZ[5];
    //
    //    for (int i = 0; i < LEG_COUNT; ++i)
    //        DEBUG_LOG(LOG_TYPE_MOVEMENT, "Leg: %d: X: %d, Y: %d, Z: %d", i, legPos[i].x, legPos[i].y, legPos[i].z);
    //
    //
    //}

    static IKLegAngles legIK(int X, int Y, int Z)
    {
        IKLegAngles ans;

        // first, make this a 2DOF problem... by solving coxa
        ans.coxa = atan2(X, Y);
        //ans.coxa = atan(Y/X);
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
        ans.tibia = acos((float)d1 / (float)d2) -1.57f;

        return ans;
    }
};


#endif