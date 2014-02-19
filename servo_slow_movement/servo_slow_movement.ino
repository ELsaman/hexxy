#include "ResetMovement.h"
#include "test.h"
#include <Arduino.h>

//#include <utility.h>
//#include <unwind-cxx.h>
//#include <system_configuration.h>
#include <StandardCplusplus.h>
////#include <TimerOne.h>
//#include <vector>
//#include <iterator>
//#include <list>
//#include <deque>
#include "HexaLeg.h"
#include <Servo.h>
#include <Timer.h>

#define DEBUG_OUTPUT

enum
{
    SERVO_COUNT         = 3,
    LEG_COUNT           = 6,
    TOTAL_SERVOS        = SERVO_COUNT * LEG_COUNT,
    DEBUG_PIN_I         = 13,
    DEBUG_PIN_O         = 12,
    MIN_MICROS          = 550,
    MAX_MICROS          = 2400
};

Servo servos[SERVO_COUNT];

unsigned long oldTime = 2L;
unsigned long timeMS = 2L;

HexaLeg * legs[LEG_COUNT];

int speeds[TOTAL_SERVOS][4] =
{
    {500, 2150, 500, 2150}, // Leg 1
    {500, 2150, 500, 2150},
    {500, 2200, 500, 2200},

    {500, 2150, 500, 2150}, // Leg 1
    {500, 2150, 500, 2150},
    {500, 2200, 500, 2200},

    {500, 2150, 500, 2150}, // Leg 1
    {500, 2150, 500, 2150},
    {500, 2200, 500, 2200},

    {500, 2150, 500, 2150}, // Leg 1
    {500, 2150, 500, 2150},
    {500, 2200, 500, 2200},

    {500, 2150, 500, 2150}, // Leg 1
    {500, 2150, 500, 2150},
    {500, 2200, 500, 2200},

    {500, 2150, 500, 2150}, // Leg 1
    {500, 2150, 500, 2150},
    {500, 2200, 500, 2200},

    // Leg 2 ...
};

// {tibia, femur, coxa}
uint8_t pins[6][3] =
{
    //{41, 37, 35},
    {40, 38, 36},
    {34, 32, 30},
    {28, 26, 24},

    {41, 39, 37},
    {35, 33, 31},
    {29, 27, 25}
};

bool IS_DEBUG_MODE      = false;

void setup()
{
    Serial.begin(115200);

    pinMode(DEBUG_PIN_I, INPUT);
    pinMode(DEBUG_PIN_O, OUTPUT);
    digitalWrite(DEBUG_PIN_O, HIGH);
    delay(500);

    if (digitalRead(DEBUG_PIN_I) == HIGH)
    {
        Serial.println("DEBUG MODE");
        IS_DEBUG_MODE = true;
    }

    delay(2000);

    digitalWrite(DEBUG_PIN_O, LOW);


    // Init servos, move to 180°
    for (int i=0; i< LEG_COUNT; ++i)
    {
        bool inv = i > 2;
        legs[i] = new HexaLeg(&(pins[i]), *(speeds + i), inv);

        if (IS_DEBUG_MODE)
        {
            Serial.print("debug movement");
            legs[i]->AddSequence(new StandupMovement(inv));
        }
        else
            legs[i]->AddSequence(new MovementSequence(inv));
    }

    //int id = 0;
    //Serial.print(0);
    //legs[0]->AddSequence(new DebugResetMovement(false));
    //
    //++id;
    ////Serial.print(id);
    ////legs[id]->AddSequence(new DebugResetMovement(id));
    //++id;
    //Serial.print(2);
    //legs[2]->AddSequence(new DebugResetMovement(false));
    //Serial.print(4);
    //legs[4]->AddSequence(new DebugResetMovement(true));

    delay(5000);
    oldTime = micros();
}

        //char buf[50];
        int cnt = 0;
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

        //Serial.print("buf ");
        //Serial.print(temp);
        //Serial.print(" size ");
        //Serial.print(size);
        //Serial.print(" temp ");
        //Serial.println(temp);
        //Serial.print("red ");
        //Serial.println(tgt[i]);
        //Serial.flush();
    }

    for (int i=0; i< LEG_COUNT; ++i)
    {
        bool inv = i > 2;
        //Serial.print("itr = ");
        //Serial.println(tarAngles[0]);

        legs[i]->AddSequence(new TargetedMovement(inv, 90));
        legs[i]->SetTargetAngle(SEGMENT_COXA, tgt[SEGMENT_COXA], false);
        legs[i]->SetTargetAngle(SEGMENT_FEMUR, tgt[SEGMENT_FEMUR], inv);
        legs[i]->SetTargetAngle(SEGMENT_TIBIA, tgt[SEGMENT_TIBIA], inv);
    }

    while (Serial.available())
        Serial.read();
    return;
    //int res = atoi(buf2);

    return;

    //Serial.readBytes(buf, 50);
    //char * tok = strtok(buf, ":");
    //int idx = 0;
    //if (strcmp(tok, "COMM_BEGIN"))
    //{
    //    //Serial.println("Invalid order");
    //    //Serial.println(tok);
    //    while(Serial.available() > 0)
    //        Serial.read();
    //    return;
    //}
    //
    //bool move = false;
    //for (int i = 0; i < 3; ++i)
    //{
    //    oldAngles[i] = tarAngles[i];
    //    tok = strtok(NULL, ":");
    //    tarAngles[i] = atoi(tok);
    //    //Serial.print(SegToText[i]);
    //    //Serial.print("\t");
    //    //Serial.println(atoi(tok));
    //
    //    if (oldAngles[i] != tarAngles[i])
    //    {
    //        //Serial.print("old: ");
    //        //Serial.println(oldAngles[i]);
    //        //Serial.print("new: ");
    //        //Serial.println(tarAngles[i]);
    //        move = true;
    //    }
    //}
    //
    //tok = strtok(NULL, ":");
    //if (tok != NULL && !strcmp(tok, "COMM_END"))
    //{
    //    //Serial.println("Got COMM_END");
    //    //Serial.println();
    //    if (move)
    //    {
    //        for (int i=0; i< LEG_COUNT; ++i)
    //        {
    //            bool inv = i > 2;
    //            //Serial.print("itr = ");
    //            //Serial.println(tarAngles[0]);
    //
    //            legs[i]->SetTargetAngle(tarAngles[0]);
    //            legs[i]->AddSequence(new TargetedMovement(inv, tarAngles[0]));
    //        }
    //    }
    //    //else
    //    //    Serial.println("No need to move");
    //}
    //else if (tok != NULL)
    //    Serial.println(tok);
    //else
    //    Serial.println("very bad");
}

void loop()
{
    if (Serial.available())
    {
        ++cnt;
        ReceiveSerial();

        //tok = strtok(NULL, ":");
        //if (tok != NULL)
        //tarAngles[idx] = atoi(tok);
        //tok = strtok(NULL, ":");
        //if (tok != NULL)
        //tarAngles[idx] = atoi(tok);
        //tok = strtok(NULL, ":");
        //if (tok != NULL)
        //tarAngles[idx] = atoi(tok);
        //tok = strtok(NULL, ":");
        //
        //if (tok != NULL && !strcmp(tok, "COMM_END"))
        //    Serial.print("All good");
        //else
        //    Serial.print("very bad");
        //while (tok != NULL && idx < 3 )
        //{
        //    //Serial.print(cnt);
        //    //Serial.print("\t");
        //    //Serial.print(idx);
        //    //Serial.print("\t");
        //    //Serial.println(tok);
        //    //Serial.flush();
        //    //char buf2[255];
        //    //sprintf(buf2, "%s:\t%u", SegToText[idx], tarAngles[idx]);
        //    //Serial.print(buf2);
        //    ++idx;
        //}
        //    Serial.println("very bad");
        //buf = Serial.readBytes
        //
        //strtok(line, ",");
        //Serial.println(line);
    }

    timeMS = micros();
    if (timeMS > oldTime)
    {
        for (int i=0; i< LEG_COUNT; ++i)
        {
            legs[i]->UpdateServos();
        }
        oldTime = micros() + 5000;
    }
}
