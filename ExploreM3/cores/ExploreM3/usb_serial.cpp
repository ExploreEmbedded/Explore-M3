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



#include "usb_serial.h"
#include <inttypes.h>
#include "type.h"

#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "cdc.h"
#include "cdcuser.h"
#include "rgb.h"

USBSerial Serial;

USBSerial::USBSerial(void) 
{
  USB_Init();                               // USB Initialization
  USB_Connect(TRUE);                        // USB Connect
  
  while (!USB_Configuration) ;              // wait until USB is configured 
}



/*
 * Set up/tear down
 */


void USBSerial::begin(uint32_t baud) 
{
/*
  USB_Init();                               // USB Initialization
  USB_Connect(TRUE);                        // USB Connect
  
  while (!USB_Configuration) ;              // wait until USB is configured   */
}




void USBSerial::end(void) {
 
}

void USBSerial::Send(uint8_t ch) {
uint32_t temp = (uint32_t)ch;
    USB_WriteEP (CDC_DEP_IN, (unsigned char *)&temp, 1);
}

/*
 * I/O
 */

int USBSerial::read(void) {
    
    char ch;
    int numBytesToRead = 1;
    // Block until a byte becomes available, to save user confusion.
    while (!this->available());
    CDC_RdOutBuf (&ch, &numBytesToRead);
		//  USB_WriteEP (CDC_DEP_IN, (unsigned char *)&serBuf[0], numBytesRead);
        
    return ch;
}

int USBSerial::available(void) {
    
  int numAvailByte;

  CDC_OutBufAvailChar (&numAvailByte);
        
    return numAvailByte;//usart_data_available(this->usart_device);
}

/* Roger Clark. Added function missing from LibMaple code */

int USBSerial::peek(void)
{
    return 0;//usart_peek(this->usart_device);
}

int USBSerial::availableForWrite(void)
{
/* Roger Clark. 
 * Currently there isn't an output ring buffer, chars are sent straight to the hardware. 
 * so just return 1, meaning that 1 char can be written
 * This will be slower than a ring buffer implementation, but it should at least work !
 */
  return 1;
}

void delay(volatile int count)
{
    volatile int i,j;
    for(i=0;i<count;i++)
        for(j=0;j<100;j++);
}

size_t USBSerial::write(unsigned char ch) {

    USB_WriteEP (CDC_DEP_IN, (unsigned char *)&ch, 1);
    delay(22);
	return 1;
}

void USBSerial::flush(void) {
 //   usart_reset_rx(this->usart_device);
}
