/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
 * Copyright (c) 2011, 2012 LeafLabs, LLC.
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *****************************************************************************/

/**
 * @file wirish/HardwareSerial.cpp
 * @brief Wirish serial port implementation.
 */

#include "HardwareSerial.h"
#include <inttypes.h>
#include "uart.h"






HardwareSerial::HardwareSerial(usart_dev *usart_device) 
{
    this->usart_device = usart_device;
}






void HardwareSerial::begin(uint32_t baud) 
{
     
        if (baud > this->usart_device->max_baud)
         {
           return;
         }

   this->usart_device->baud_rate = baud; 
    usart_init(this->usart_device);        
	
}




void HardwareSerial::end(void) {
   
}

void HardwareSerial::Send(uint8_t ch) {

    usart_putc(this->usart_device, ch);
	//return 1;
}



int HardwareSerial::read(void) { 
    return usart_getc(this->usart_device);
}

int HardwareSerial::available(void) {
    return 1; //Retruns 1 indicating data is available, While reding a char it waits till a char is received.
}



int HardwareSerial::peek(void)
{
    return 0;//usart_peek(this->usart_device);
}

int HardwareSerial::availableForWrite(void)
{
/* Currently there isn't an output ring buffer, chars are sent straight to the hardware. 
 * so just return 1, meaning that 1 char can be written.
 * This will be slower than a ring buffer implementation.
 */
  return 1;
}

size_t HardwareSerial::write(unsigned char ch) {

    usart_putc(this->usart_device, ch);
	return 1;
}

void HardwareSerial::flush(void) {
  //As the ring buffer is not used nothing is there to flush, Just included for compilation.
}
