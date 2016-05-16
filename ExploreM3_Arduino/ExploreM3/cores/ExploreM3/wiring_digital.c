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

extern void pinMode( uint32_t ulPin, uint32_t ulMode )
{
   if(ulPin<BOARD_MAX_GPIO_PINS)
   GPIO_PinDirection(PIN_MAP[ulPin],ulMode);
}

extern void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
    if(ulPin<BOARD_MAX_GPIO_PINS)
    GPIO_PinWrite(PIN_MAP[ulPin],ulVal);
}

extern int digitalRead( uint32_t ulPin )
{
    int value=0;
    
  if(ulPin<BOARD_MAX_GPIO_PINS)
     value = GPIO_PinRead(PIN_MAP[ulPin]);
 
	return value;
}


void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value) {
    digitalWrite(clockPin, LOW);
    for (int i = 0; i < 8; i++) 
    {  
        int bit = bitOrder == LSBFIRST ? i : (7 - i);

        digitalWrite(dataPin, (value >> bit) & 0x1);
		digitalWrite(clockPin, HIGH); 
        digitalWrite(clockPin, LOW);
    }
}

    
#ifdef __cplusplus
}
#endif

