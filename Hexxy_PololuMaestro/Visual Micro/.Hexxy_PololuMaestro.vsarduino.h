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

#include "C:\Program Files (x86)\Arduino\hardware\arduino\cores\arduino\arduino.h"
#include "C:\Program Files (x86)\Arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\hexxy\Hexxy_PololuMaestro\Hexxy_PololuMaestro.ino"
#include "C:\hexxy\Hexxy_PololuMaestro\Common.h"
#include "C:\hexxy\Hexxy_PololuMaestro\Defines.h"
#include "C:\hexxy\Hexxy_PololuMaestro\IKCalculator.cpp"
#include "C:\hexxy\Hexxy_PololuMaestro\IKCalculator.h"
#include "C:\hexxy\Hexxy_PololuMaestro\InputMgr.cpp"
#include "C:\hexxy\Hexxy_PololuMaestro\InputMgr.h"
#include "C:\hexxy\Hexxy_PololuMaestro\PololuMgr.cpp"
#include "C:\hexxy\Hexxy_PololuMaestro\PololuMgr.h"
#include "C:\hexxy\Hexxy_PololuMaestro\SerialMgr.cpp"
#include "C:\hexxy\Hexxy_PololuMaestro\SerialMgr.h"
#include "C:\hexxy\Hexxy_PololuMaestro\Util.cpp"
#include "C:\hexxy\Hexxy_PololuMaestro\Util.h"
#include "C:\hexxy\Hexxy_PololuMaestro\ft.cpp"
#include "C:\hexxy\Hexxy_PololuMaestro\ft.h"
#endif
