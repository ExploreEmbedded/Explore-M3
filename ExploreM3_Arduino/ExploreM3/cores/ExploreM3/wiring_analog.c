/*
 Copyright (c) 2011 Arduino.  All right reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 See the GNU Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "Arduino.h"


#ifdef __cplusplus
extern "C" {
#endif









uint32_t analogRead(uint32_t ulPin)
{
  uint32_t ulValue = 0;
  /* read the analog value only if the pin is within range */
   if((ulPin>=ANALOG_ZERO) && (ulPin<=ANALOG_MAX))
    {
      ulValue = ADC_GetAdcValue(PIN_MAP[ulPin]);
    }
    
	return ulValue;
}






void analogOutputInit(void) {

}

// Right now, PWM output only works on the pins with
// hardware support.  These are defined in the appropriate
// pins_*.c file.  For the rest of the pins, we default
// to digital output.
void analogWrite(uint32_t ulPin, uint32_t ulValue) {

 if(ulPin<BOARD_MAX_GPIO_PINS)   
     PWM_Set(PIN_MAP[ulPin],ulValue);    
}



#ifdef __cplusplus
}
#endif
