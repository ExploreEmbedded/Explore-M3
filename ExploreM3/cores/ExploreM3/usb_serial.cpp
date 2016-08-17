/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2015 ExploreEmbedded.com
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
#include "wirish_time.h"

USBSerial Serial;

USBSerial::USBSerial(void) 
{
  USB_Init();                               // USB Initialization
  USB_Connect(TRUE);                        // USB Connect
  
  while (!USB_Configuration) ;              // wait until USB is configured 
  delay(1000);
}



/*
 * Set up/tear down
 */


void USBSerial::begin(uint32_t baud) 
{
    /* ExploreEmbedded:
     * USB_Initialization done in constructor itself, so USB_Serial class is always enabled.*/
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



int USBSerial::read(void) {
    
    char ch;
    int numBytesToRead = 1;

    while (!this->available()); //Wait till the ringbufffer is empty
    CDC_RdOutBuf (&ch, &numBytesToRead);
        
    return ch;
}

int USBSerial::available(void) {
    
  int numAvailByte;

  CDC_OutBufAvailChar (&numAvailByte);
        
    return numAvailByte;
}



int USBSerial::peek(void)
{
    return 0;
}

int USBSerial::availableForWrite(void)
{
/* ExploreEmbedded. 
 * Currently ring buffer is not implemented for Tx, chars are sent straight to the hardware. 
 * so just return 1, meaning that 1 char can be written
 */
  return 1;
}


extern volatile int TxDoneFlag; //Flag to indicate the USB frame is transmitted.
size_t USBSerial::write(unsigned char ch) {

    USB_WriteEP (CDC_DEP_IN, (unsigned char *)&ch, 1);

  while(TxDoneFlag==0); //This falg will be set by USB EndPoint2 Tx call back function.
      TxDoneFlag = 0;
	return 1;
}

void USBSerial::flush(void) {
 
}
