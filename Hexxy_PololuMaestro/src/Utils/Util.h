#ifndef UTIL_H
#define UTIL_H

#include "Arduino.h"

#define DEBUG_OUTPUT

#define ARRAY_SIZE(x) ((sizeof x) / (sizeof *x))


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

static bool logEnabled[LOG_TYPE_MAX] =
{
    true,           // LOG_TYPE_COMM
    true           // LOG_TYPE_MOVEMENT
};

extern void DEBUG_LOG(LogType type, const char * format, ...);

#endif