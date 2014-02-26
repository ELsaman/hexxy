// 
// 
// 

#include "Hexapod.h"

void Hexapod::_Init()
{
    for (int i = 0; i < LEG_COUNT; ++i)
    {
        for (int j = 0; j < TOTAL_SEGMENTS; ++j)
        {
            _servoPins[i][j] = 0;
        }

        _legs[i] = NULL;
    }
}

void Hexapod::SetupLegs()
{
    for (int i = 0; i < LEG_COUNT; ++i)
        _legs[i] = new HexapodLeg(_servoPins[i], i > 2);
}

void Hexapod::UpdateLegs()
{
    for (int i = 0; i < LEG_COUNT; ++i)
    {
        _legs[i]->UpdateSegments();
    }
}


Hexapod HEXAPOD;

