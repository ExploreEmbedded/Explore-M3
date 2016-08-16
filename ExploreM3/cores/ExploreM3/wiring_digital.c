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
   
   GPIO_PinDirection(PIN_MAP[ulPin],ulMode);
}

extern void digitalWrite( uint32_t ulPin, uint32_t ulVal )
{
    
    GPIO_PinWrite(PIN_MAP[ulPin],ulVal);
}

extern int digitalRead( uint32_t ulPin )
{
    int value=0;
    
 
     value = GPIO_PinRead(PIN_MAP[ulPin]);
 
	return value;
}


void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t value) {
      
    if(bitOrder == LSBFIRST )
    {
       for (int bit = 0; bit < 8; bit++) 
        {  
          GPIO_PinWrite(PIN_MAP[dataPin], (value >> bit) & 0x1);
		  GPIO_PinWrite(PIN_MAP[clockPin], HIGH); 
          GPIO_PinWrite(PIN_MAP[clockPin], LOW);
        }
    }
    else
    {
        for (int bit = 7; bit >= 0; bit--) 
        {  
          GPIO_PinWrite(PIN_MAP[dataPin], (value >> bit) & 0x1);
		  GPIO_PinWrite(PIN_MAP[clockPin], HIGH); 
          GPIO_PinWrite(PIN_MAP[clockPin], LOW);
        }  
    }
}

    
#ifdef __cplusplus
}
#endif

