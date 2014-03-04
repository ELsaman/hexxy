#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Mega 2560 or Mega ADK
#define __AVR_ATmega2560__
#define ARDUINO 105
#define ARDUINO_MAIN
#define __AVR__
#define __avr__
#define F_CPU 16000000L
#define __cplusplus
#define __inline__
#define __asm__(x)
#define __extension__
#define __ATTR_PURE__
#define __ATTR_CONST__
#define __inline__
#define __asm__ 
#define __volatile__

#define __builtin_va_list
#define __builtin_va_start
#define __builtin_va_end
#define __DOXYGEN__
#define __attribute__(x)
#define NOINLINE __attribute__((noinline))
#define prog_void
#define PGM_VOID_P int
            
typedef unsigned char byte;
extern "C" void __cxa_pure_virtual() {;}

//
//
void ReceiveSerial();

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\hexxy\Hexapod_new\Hexapod_new.ino"
#include "C:\hexxy\Hexapod_new\Defines.h"
#include "C:\hexxy\Hexapod_new\Hexapod.cpp"
#include "C:\hexxy\Hexapod_new\Hexapod.h"
#include "C:\hexxy\Hexapod_new\HexapodLeg.cpp"
#include "C:\hexxy\Hexapod_new\HexapodLeg.h"
#include "C:\hexxy\Hexapod_new\Hexxy.cpp"
#include "C:\hexxy\Hexapod_new\Hexxy.h"
#include "C:\hexxy\Hexapod_new\Movement.h"
#include "C:\hexxy\Hexapod_new\MovementSequence.c"
#include "C:\hexxy\Hexapod_new\MovementSequence.h"
#include "C:\hexxy\Hexapod_new\SegmentServo.cpp"
#include "C:\hexxy\Hexapod_new\SegmentServo.h"
#include "C:\hexxy\Hexapod_new\TargetedMovement.h"
#include "C:\hexxy\Hexapod_new\Util.h"
#endif
