#include "Step.h"
#include "Util.h"
#include "InputMgr.h"

LegStep::LegStep(uint8_t startPhase, int xMod) : phase(startPhase), tickCnt(0), oldSpeedX(0.0f), oldSpeedY(0.0f), _startPhase(startPhase), _xMod(xMod)
{
    static bool isLogger = false;

    if (!isLogger)
    {
        logging = true;
        isLogger = true;
    }
    CalcSpeed();
}

bool LegStep::CalcSpeed()
{

    InputState * state = sInputMgr.getCurrentState();

    if (!state->isMoving())
    {
        //DEBUG_LOG(LOG_TYPE_COMM, "NotMoving");
        phase = -1;
        return false;
    }


    float speedX = (float)state->getSpeedX() * 0.07f;
    float speedY = (float)state->getSpeedY() * 0.04f;
    float speedR = 0.0f;


    oldSpeedX = speedX;
    oldSpeedY = speedY;

    //speedX *= 0.07f;
    //speedY *= 0.07f;

    for (int i = 0; i < STEP_PHASE_CNT; ++i)
    {
        StepPosition & tick = valPerTick[i];

        ticksPerPhase[i] = phaseSteps[i].timer / UPDATE_TIMER;

        // steps per tick
        tick.x = float(phaseSteps[i + 1].pos.x - phaseSteps[i].pos.x) * speedX / (float)ticksPerPhase[i];
        tick.y = float(phaseSteps[i + 1].pos.y - phaseSteps[i].pos.y) * speedY / (float)ticksPerPhase[i];
        tick.z = float(phaseSteps[i + 1].pos.z - phaseSteps[i].pos.z) / (float)ticksPerPhase[i];
        //DEBUG_LOG(LOG_TYPE_COMM, "phase: %d ticks: %d, step 0.%d", i, ticksPerPhase[i], int(tick.z * 100.0f));
        //DEBUG_LOG(LOG_TYPE_COMM, "phase: %d ticks: %d,", i, ticksPerPhase[i]);
    }

    return true;
}

void LegStep::Update()
{
    //return;
    if (phase == -1)
    {
        if (CalcSpeed())
            phase = _startPhase;
    } else if (!sInputMgr.getCurrentState()->isMoving())
    {
        phase = -1;
        return;
    }

    if (phase >= 3 || phase < 0)
        return;

    if (tickCnt >= ticksPerPhase[phase])
    {
        uint8_t phaseTemp = phase;
        tickCnt = 0;

        if (phase == 2)
            phase = 0;
        else
            ++phase;

        if (phase == _startPhase)
            CalcSpeed();

        //DEBUG_LOG(LOG_TYPE_COMM, "%d new phase  %d, %d", phaseTemp, phase, ticksPerPhase[phase]);
    } else ++tickCnt;
}

void LegStep::Init()
{

}


void LegStep::GetCurrentPos(int &x, int &y, int &z)
{
    if (phase == -1)
    {
        x = phaseSteps[_startPhase].pos.x + _xMod;
        y = phaseSteps[_startPhase].pos.y;
        z = phaseSteps[_startPhase].pos.z;
        return;
    }

    x = phaseSteps[phase].pos.x * oldSpeedX + _xMod;
    y = phaseSteps[phase].pos.y * oldSpeedY;
    z = phaseSteps[phase].pos.z;

    if (phase >= STEP_PHASE_CNT)
    {
        return;
    }

    x += int(valPerTick[phase].x * (float)tickCnt);
    y += int(valPerTick[phase].y * (float)tickCnt);
    z += int(valPerTick[phase].z * (float)tickCnt);

}
