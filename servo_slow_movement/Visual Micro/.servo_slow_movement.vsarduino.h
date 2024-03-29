#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
//Board = Arduino Uno
#define __AVR_ATmega328p__
#define __AVR_ATmega328P__
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
void ReceiveSerial();
//

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\standard\pins_arduino.h" 
#include "C:\hexxy\servo_slow_movement\servo_slow_movement.ino"
#include "C:\hexxy\servo_slow_movement\Defines.h"
#include "C:\hexxy\servo_slow_movement\HexaLeg.h"
#include "C:\hexxy\servo_slow_movement\HexaLeg.ino"
#include "C:\hexxy\servo_slow_movement\HexaLegSegment.h"
#include "C:\hexxy\servo_slow_movement\HexaLegSegment.ino"
#include "C:\hexxy\servo_slow_movement\MovementSequence.cpp"
#include "C:\hexxy\servo_slow_movement\MovementSequence.h"
#include "C:\hexxy\servo_slow_movement\ResetMovement.cpp"
#include "C:\hexxy\servo_slow_movement\ResetMovement.h"
#include "C:\hexxy\servo_slow_movement\TripodMovement.h"
#include "C:\hexxy\servo_slow_movement\test.cpp"
#include "C:\hexxy\servo_slow_movement\test.h"
#endif
