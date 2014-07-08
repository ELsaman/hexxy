/* 
	Editor: http://www.visualmicro.com
	        visual micro and the arduino ide ignore this code during compilation. this code is automatically maintained by visualmicro, manual changes to this file will be overwritten
	        the contents of the Visual Micro sketch sub folder can be deleted prior to publishing a project
	        all non-arduino files created by visual micro and all visual studio project or solution files can be freely deleted and are not required to compile a sketch (do not delete your own code!).
	        note: debugger breakpoints are stored in '.sln' or '.asln' files, knowledge of last uploaded breakpoints is stored in the upload.vmps.xml file. Both files are required to continue a previous debug session without needing to compile and upload again
	
	Hardware: Arduino Mega 2560 or Mega ADK, Platform=avr, Package=arduino
*/

#ifndef _VSARDUINO_H_
#define _VSARDUINO_H_
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
bool normalize(int &angle);
//
void DoKinematics(LegIds legNum, int StepX, int StepY, int StepZ, const IKBodyMods * bodyMods);

#include "c:\Program Files (x86)\arduino\hardware\arduino\cores\arduino\arduino.h"
#include "c:\Program Files (x86)\arduino\hardware\arduino\variants\mega\pins_arduino.h" 
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\Hexxy_PololuMaestro.ino"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\Common.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\Defines.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\Gait.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\GaitSequencer.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\GaitSequencer.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\IKCalculator.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\IKCalculator.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\InputMgr.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\InputMgr.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\PololuMgr.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\PololuMgr.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\SerialMgr.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\SerialMgr.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\Step.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\Step.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\TripodGait.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\Util.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\Util.h"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\ft.cpp"
#include "C:\hexxy_temp\Temp_hexxy\Hexxy_PololuMaestro\ft.h"
#endif
