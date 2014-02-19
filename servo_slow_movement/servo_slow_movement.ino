#include "ResetMovement.h"
#include "test.h"
#include <Arduino.h>
#include <StandardCplusplus.h>
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

    delay(5000);
    oldTime = micros();
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

        legs[i]->AddSequence(new TargetedMovement(inv, 90));
        legs[i]->SetTargetAngle(SEGMENT_COXA, tgt[SEGMENT_COXA], false);
        legs[i]->SetTargetAngle(SEGMENT_FEMUR, tgt[SEGMENT_FEMUR], inv);
        legs[i]->SetTargetAngle(SEGMENT_TIBIA, tgt[SEGMENT_TIBIA], inv);
    }

    while (Serial.available())
        Serial.read();
}

void loop()
{
    if (Serial.available())
        ReceiveSerial();

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
