// Hexxy.h

#ifndef _HEXXY_h
#define _HEXXY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "Hexapod.h"

class Hexxy : public Hexapod
{
public:
    Hexxy() : Hexapod() {}
    void Init();
};

//extern Hexxy HEXXY;

#endif

