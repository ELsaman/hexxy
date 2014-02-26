// 
// 
// 

#include "Hexapod.h"
#include "Hexxy.h"

    void Hexxy::Init()
    {
        uint8_t pins[LEG_COUNT][TOTAL_SEGMENTS] = 
        {
            { 40, 38, 36 },
            { 34, 32, 30 },
            { 28, 26, 24 },

            { 41, 39, 37 },
            { 35, 33, 31 },
            { 29, 27, 25 }
        };


        for (int i = 0; i < LEG_COUNT; ++i)
        {
            for (int j = 0; j < TOTAL_SEGMENTS; ++j)
            {
                _servoPins[i][j] = pins[i][j];
                int temp = _servoPins[i][j];
                
            }
        }

        SetupLegs();
    }

