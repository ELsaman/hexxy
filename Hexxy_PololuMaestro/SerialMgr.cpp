#include "SerialMgr.h"
#include "InputMgr.h"
#include "Arduino.h"
#include "Util.h"

void SerialMgr::Update()
{
    if (readLine(Serial.read(), buffer, 255) > 0)
        parseLine();
}

void SerialMgr::parseLine()
{
    char(command)[5] = {'\0'};
    memcpy(command, buffer,4  * sizeof(char));

    for (int i = 0; i < COMMAND_TOTAL; ++i)
    {
        if (strcmp(command, commandChars[i]) == 0)
        {
            DEBUG_LOG(LOG_TYPE_COMM, "Handling command %s", commandChars[i]);
            handleCommand(InputCommands(i));
            return;
        }
    }

    DEBUG_LOG(LOG_TYPE_COMM, "Unknown command %s received", command);
}

void SerialMgr::readNumData(std::vector<char*> &output)
{
    char * temp = strtok(&buffer[5], " ");

    while (temp != NULL)
    {
        output.push_back(temp);
        temp = strtok(NULL, " ");
    }
}

// Command example: "DCTA 180 1000 1 2000 DCTA\r"

void SerialMgr::handleCommand(InputCommands cmd)
{
    if (cmd > COMMAND_TOTAL)
        return;

    int pos = 5; // CMD LENGTH
    std::vector<char*> parsed;
    readNumData(parsed);

    if (strcmp(parsed.back(), commandChars[cmd]) != 0)
    {
        DEBUG_LOG(LOG_TYPE_COMM, "Command missing end token");
        return;
    }

    switch (cmd)
    {
        case COMMAND_DCTA:
        {
            if (parsed.size() != 5)
                return; // TODO: error handling

            

            float angle = float(atof(parsed[0]) * DEG_TO_RAD);
            float speed = float(atof(parsed[1]) / 10.0f);
            bool hasRotation = bool(atoi(parsed[2]));
            float rotation = 0.0f;
            if (hasRotation)
                 rotation = float(atof(parsed[3]) * DEG_TO_RAD);

            sInputMgr.setCurrentState(InputState(angle, speed, rotation));
            //DEBUG_LOG(LOG_TYPE_COMM, "DCTA angle: %f, speed: %f, rotation: %f", angle, speed, rotation);
            
            break;
        }
        case COMMAND_DCTC:
        case COMMAND_GAIT:
        case COMMAND_MODE:
        default:
            break;
    }
}

// http://hacking.majenko.co.uk/reading-serial-on-the-arduino

int8_t SerialMgr::readLine(int readch, char *buffer, int len)
{
    static int pos = 0;
    int rpos;

    if (readch > 0)
    {
        switch (readch)
        {
            case '\n': // Ignore new-lines
                break;
            case '\r': // Return on CR
                rpos = pos;
                pos = 0;  // Reset position index ready for next time
                return rpos;
            default:
                if (pos < len - 1)
                {
                    buffer[pos++] = readch;
                    buffer[pos] = 0;
                }
        }
    }
    // No end of line has been found, so return -1.
    return -1;
}