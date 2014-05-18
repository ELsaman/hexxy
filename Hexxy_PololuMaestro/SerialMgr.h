#ifndef SERIAL_MGR_H
#define SERIAL_MGR_H

#include "Util.h"
#include <StandardCplusplus.h>
#include <vector>

enum InputCommands
{
    COMMAND_DCTA,
    COMMAND_DCTC,
    COMMAND_MODE,
    COMMAND_GAIT,
    COMMAND_TOTAL
};

static const char commandChars[COMMAND_TOTAL][5] =
{
    "DCTA",
    "DCTC",
    "MODE",
    "GAIT"
};
#define make_sub_array(type, arr, off, len) (type (&)[len])(*(arr + off));

static char buffer[255] = { 0 };

class SerialMgr
{
public:
    static SerialMgr & instance()
    {
        static SerialMgr manager;
        return manager;
    }

    void Update();

    bool parseDCTA();
    //static SerialMgr * _instance;

private:
    void parseLine();
    void handleCommand(InputCommands command);
    void readNumData(std::vector<char*> &output);

    int8_t readLine(int readch, char *buffer, int len);
    SerialMgr() {};
    ~SerialMgr() {};
};

#define sSerialMgr SerialMgr::instance()

#endif