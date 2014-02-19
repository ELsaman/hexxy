// ResetMovement.h

#ifndef _RESETMOVEMENT_h
#define _RESETMOVEMENT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

class ResetMovement
{
 private:


 public:
	void init();
};

extern ResetMovement RESETMOVEMENT;

#endif

