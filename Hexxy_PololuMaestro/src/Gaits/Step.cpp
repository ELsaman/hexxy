#include "Step.h"
#include "Util.h"
#include "InputMgr.h"

LegStep::LegStep(uint8_t startPhase) : phase(startPhase), tickCnt(0), oldSpeedX(0.0f), oldSpeedY(0.0f), _startPhase(startPhase)
{
    //CalcStepPerTick();
    //memset(valPerTick, 0, sizeof(valPerTick));

    //CalcSpeed();
    //return;
    CalcSpeed();
    return;
    InputState * state = sInputMgr.getCurrentState();


    float speedX = 5.0f;
    float speedY = 5.0f;
    float speedR = 0.0f;

    if (speedX < 1.0f || speedY < 1.0f)
        return;

    for (int i = 0; i < STEP_PHASE_CNT; ++i)
    {
        StepPosition & pos = valPerTick[i];
    
        ticksPerPhase[i] = phaseSteps[i].timer / UPDATE_TIMER;


        // steps per tick
        pos.x = float(phaseSteps[i + 1].pos.x - phaseSteps[i].pos.x) * speedX / (float)ticksPerPhase[i];
        pos.y = float(phaseSteps[i + 1].pos.y - phaseSteps[i].pos.y) * speedY / (float)ticksPerPhase[i];
        pos.z = float(phaseSteps[i + 1].pos.z - phaseSteps[i].pos.z) / (float)ticksPerPhase[i];
        //DEBUG_LOG(LOG_TYPE_COMM, "asda %d, %d, %d,", phaseSteps[i].pos.x, phaseSteps[i].pos.y, phaseSteps[i].pos.z);
    }
}

bool LegStep::CalcSpeed()
{
    InputState * state = sInputMgr.getCurrentState();

    if (!state->isMoving())
    {
        phase = -1;
        //DEBUG_LOG(LOG_TYPE_COMM, "Calculating Speed: X: %d, Y: %d", (int)speedX, (int)speedY);
        return false;
    }



    float speedX = state->getSpeedX();
    float speedY = state->getSpeedY();



    //DEBUG_LOG(LOG_TYPE_COMM, "Calculating Speed: X: %d, Y: %d", (int)speedX, (int)speedY);

    speedX = 30.0f * speedX / 100.0f;
    speedY = 30.0f * speedY / 100.0f;
    //DEBUG_LOG(LOG_TYPE_COMM, "Calculated Speed: X: %d, Y: %d", (int)speedX, (int)speedY);
    float speedR = 0.0f;

    if (oldSpeedX == speedX && oldSpeedY == speedY)
        return false;


    DEBUG_LOG(LOG_TYPE_COMM, "Moving %d", _startPhase);

    oldSpeedX = speedX;
    oldSpeedY = speedY;

    for (int i = 0; i < STEP_PHASE_CNT; ++i)
    {
        StepPosition & pos = valPerTick[i];

        ticksPerPhase[i] = phaseSteps[i].timer / UPDATE_TIMER;


        // steps per tick
        pos.x = float(phaseSteps[i + 1].pos.x - phaseSteps[i].pos.x) * speedX / (float)ticksPerPhase[i];
        pos.y = float(phaseSteps[i + 1].pos.y - phaseSteps[i].pos.y) * speedY / (float)ticksPerPhase[i];
        pos.z = float(phaseSteps[i + 1].pos.z - phaseSteps[i].pos.z) / (float)ticksPerPhase[i];
        //DEBUG_LOG(LOG_TYPE_COMM, "asda %d, %d, %d,", phaseSteps[i].pos.x, phaseSteps[i].pos.y, phaseSteps[i].pos.z);
    }

    return true;
}

void LegStep::CalcStepPerTick()
{

    float speedX = 20.0f;
    float speedY = 0.0f;
    float speedR = 0.0f;

    for (int i = 0; i < STEP_PHASE_CNT; ++i)
    {

        StepPosition & pos = valPerTick[i];

//        ticksPerPhase[i] = (phaseSteps[i].timer - phaseSteps[i].timer * speedX / 100.0f) / UPDATE_TIMER;
        ticksPerPhase[i] = phaseSteps[i].timer / UPDATE_TIMER;
        
#define DEFAULT_STEP        100.0f

        switch (i)
        {
            case 0: // Leg is in the back
                pos.x = speedX * DEFAULT_STEP / (100 * (float)ticksPerPhase[i]);
                pos.y = speedX * DEFAULT_STEP / (100 * (float)ticksPerPhase[i]);
                pos.z = 0.0f;
                pos.r = 0.0f;
                break;
            case 1: // Leg lifted up
                pos.x = 0.0f;
                pos.y = 0.0f;
                pos.z = -90.0f / (float)ticksPerPhase[i]; // default leg lift height
                pos.r = 0.0f;
                break;
            case 2: // Leg pulled back
                pos.x = -speedX * DEFAULT_STEP * 2 / (100 * (float)ticksPerPhase[i]);
                pos.y = -speedX * DEFAULT_STEP / (100 * (float)ticksPerPhase[i]);
                pos.z = 90.0f / (float)ticksPerPhase[i];
                pos.r = 0.0f;
                break;
        }
    }
}

void LegStep::Update()
{
 
    if (phase >= 3)
    {
        if (CalcSpeed())
            phase = 0;
    }
    if (phase < 0)
    {
        if (CalcSpeed())
            phase = _startPhase;

    }

    if (!sInputMgr.getCurrentState()->isMoving())
    {
        if (phase >= 0)
        {
            DEBUG_LOG(LOG_TYPE_COMM, "Stopped %d", _startPhase);
            phase = -1;
        }
        return;
    }


    
    //CalcSpeed();

    //if (fabs(oldSpeedX) < 1.0f && fabs(oldSpeedY) < 1.0f)
      //  return;

    if (tickCnt >= ticksPerPhase[phase])
    {
        // reached end of the phase - next one
        tickCnt = 0;
        ++phase;
    } else
        ++tickCnt;

}

void LegStep::GetCurrentPos(int &x, int &y, int &z)
{
    if (phase < 0)
    {
        x = phaseSteps[_startPhase].pos.x;
        y = phaseSteps[_startPhase].pos.y;
        z = phaseSteps[_startPhase].pos.z;
        return;
    }

    x = phaseSteps[phase].pos.x;
    y = phaseSteps[phase].pos.y;
    z = phaseSteps[phase].pos.z;

    if (phase >= 3)
        return;


    x += int(valPerTick[phase].x * (float)tickCnt);
    y += int(valPerTick[phase].y * (float)tickCnt);
    z += int(valPerTick[phase].z * (float)tickCnt);
}