#ifndef UTIL_H
#define UTIL_H

#include "Arduino.h"

#define DEBUG_OUTPUT

#define DEG_TO_RAD_F 0.017453292519943295769236907684886f
#define RAD_TO_DEG_F 57.295779513082320876798154814105f
#define PI_F 3.1415926535897932384626433832795f
#define HALF_PI_F 1.5707963267948966192313216916398f

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))

#define PC_SERIAL_BAUD      115200
#define CONTROLLER_BAUD  38400

enum LogType
{
    LOG_TYPE_COMM, // Serial Communication
    LOG_TYPE_MOVEMENT,
    LOG_TYPE_MAX
};

static const String logTypeNames[LOG_TYPE_MAX] =
{
    "COMM",
    "MOVEMENT"
};

static const char *  legNames[] =
{
    "LEG_RIGHT_FRONT",
    "LEG_RIGHT_MIDDLE",
    "LEG_RIGHT_BACK",
    "LEG_LEFT_FRONT",
    "LEG_LEFT_MIDDLE",
    "LEG_LEFT_BACK"
};

static const char * segmentNames[] =
{
    "SEGMENT_COXA",
    "SEGMENT_FEMUR",
    "SEGMENT_TIBIA",
    "SEGMENT_MAX"
};

static bool logEnabled[LOG_TYPE_MAX] =
{
    true,           // LOG_TYPE_COMM
    true           // LOG_TYPE_MOVEMENT
};

extern void DEBUG_LOG(LogType type, const char * format, ...);

#endif