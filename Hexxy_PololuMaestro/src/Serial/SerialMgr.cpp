#include "SerialMgr.h"
#include "InputMgr.h"
#include "IKCalculator.h"
#include "Arduino.h"
#include "Util.h"

SerialMgr::SerialMgr()
{
    Serial3.begin(38400);
}

void SerialMgr::Update()
{
    if (!Serial3.available())
        return;
    if (readLine(Serial3.read(), buffer, 255) > 0)
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
            //DEBUG_LOG(LOG_TYPE_COMM, "Handling command %s", commandChars[i]);
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
            if (parsed.size() > 5 || parsed.size() < 2)
            {
                DEBUG_LOG(LOG_TYPE_COMM, "DCTA parsing error, size: %d", parsed.size());
                return; // TODO: error handling
            }

            //float angle = float(atof(parsed[0]) * DEG_TO_RAD_F);
            int speedX = atoi(parsed[0]);
            int speedY = atoi(parsed[1]);

            //float speed = float(atof(parsed[1]) / 10.0f);
            bool hasRotation = atoi(parsed[2]) ? true : false;
            float rotation = 0.0f;
            if (hasRotation)
                 rotation = float(atof(parsed[3]) * DEG_TO_RAD_F);

            IKBodyMods mods = IKBodyMods();
            mods.rotZ = rotation;

            //DEBUG_LOG(LOG_TYPE_COMM, "Got DCTA: %d, %d", speedX, speedY);

            sInputMgr.setCurrentState(InputState(speedX, speedY, mods));
//            DEBUG_LOG(LOG_TYPE_COMM, "DCTA angle: %d, speed: %d, rotation: %f", speedX, speedY);
            
            break;
        }
        case COMMAND_DCTP:
            // RotX RotY RotZ PosX PosY
        {
            if (parsed.size() != 6)
            {
                DEBUG_LOG(LOG_TYPE_COMM, "DCTP: Invalid options count: %u", parsed.size());
                return;
            }

            IKBodyMods mods = IKBodyMods();
            mods.rotX = atoi(parsed[0]) * DEG_TO_RAD_F;
            mods.rotY = atoi(parsed[1]) * DEG_TO_RAD_F;
            mods.rotZ = atoi(parsed[2]) * DEG_TO_RAD_F;
            mods.posX = atoi(parsed[3]);
            mods.posY = atoi(parsed[4]);
            //DEBUG_LOG(LOG_TYPE_COMM, "rot: %s %d", parsed[1], int(mods.rotY * 100.0f));
            sInputMgr.setCurrentState(InputState(0, 0, mods));


            //DEBUG_LOG(LOG_TYPE_COMM, "DCTP: pitch: 0.%d", );

            break;
        }
        case COMMAND_DCTH:
        {
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
    //DEBUG_LOG(LOG_TYPE_COMM, "got char %s", String((char)readch).c_str());
    static int pos = 0;
    int rpos;

    if (readch > 0)
    {
        switch (readch)
        {
            case '\n': // Ignore new-lines
                //DEBUG_LOG(LOG_TYPE_COMM, "got newline");
                break;
            case '\r': // Return on CR
                //DEBUG_LOG(LOG_TYPE_COMM, "got carriage return");
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