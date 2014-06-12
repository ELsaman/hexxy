#include "Util.h"

extern "C" int atexit(void(*func)(void)) { return 0; }

void DEBUG_LOG(LogType type, const char * format, ...)
{
#ifdef DEBUG_OUTPUT
    if (!logEnabled[type])
        return;

    char buffer[256];
    va_list args;
    va_start(args, format);
    vsprintf(buffer, format, args);
    va_end(args);
    Serial3.println(buffer);
#endif
}