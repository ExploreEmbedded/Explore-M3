/**************************************************************************//**
 * @file     core_cm3.h
 * @brief    CMSIS Cortex-M3 Core Peripheral Access Layer Header File
 * @version  V1.30
 * @date     30. October 2009
 *
 * @note
 * Copyright (C) 2009 ARM Limited. All rights reserved.
 *
 * @par
 * ARM Limited (ARM) is supplying this software for use with Cortex-M 
 * processor based microcontrollers.  This file can be freely distributed 
 * within development tools that are supporting such ARM based processors. 
 *
 * @par
 * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 ******************************************************************************/

#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stdutils.h"
#include "gpio.h"
#include "rgb.h"
#include "adc.h"
#include "uart.h"
#include "pwm.h"
#include "board.h"
#include "systick.h"
#include "exti.h"
#include "timer.h"



#include "wiring_digital.h"
#include "wiring_analog.h"
#include "wirish_time.h"
//#include "WCharacter.h"





extern void loop();
extern void setup();
extern void init( void );

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

#ifdef __cplusplus
} // extern "C"

#include "WCharacter.h"
#include "WString.h"
//#include "Tone.h"
//#include "WMath.h"
//#include "HardwareSerial.h"
#include "Stream.h"

#include "usb_serial.h"
#include "wirish_math.h"



#endif // __cplusplus



#endif /* __ARDUINO_H__ */

/*lint -restore */
