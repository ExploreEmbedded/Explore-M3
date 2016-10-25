

#ifndef __ARDUINO_H__
#define __ARDUINO_H__

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "stdutils.h"
#include "bit_constants.h"
#include "gpio.h"
#include "rgb.h"
#include "adc.h"
#include "pwm.h"
#include "board.h"
#include "systick.h"
#include "exti.h"
#include "timer.h"
#include "uart.h"
#include "delay.h"





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
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout);

#ifdef __cplusplus
} // extern "C"

#include "WCharacter.h"
#include "WString.h"
//#include "Tone.h"
//#include "WMath.h"
#include "HardwareSerial.h"
#include "Stream.h"
#include "eeprom.h"

#include "usb_serial.h"
#include "wirish_math.h"

#endif // __cplusplus

#ifdef __cplusplus
unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout = 1000000L);
#endif

#endif /* __ARDUINO_H__ */

/*lint -restore */
