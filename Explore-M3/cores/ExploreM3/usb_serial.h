/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @brief Wirish USB virtual serial port (SerialUSB).
 */

#ifndef _WIRISH_USB_SERIAL_H_
#define _WIRISH_USB_SERIAL_H_

#include "Print.h"
#include "Stream.h"
#include "wirish_time.h"


/**
 * @brief Virtual serial terminal.
 */
class USBSerial : public Stream {

public:
    USBSerial(void);

    /* Set up/tear down */
    void begin(uint32_t baud);
    void end();
    void Send(uint8_t ch);
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    inline size_t write(unsigned long n) { return write((uint8_t)n); }
    inline size_t write(long n) { return write((uint8_t)n); }
    inline size_t write(unsigned int n) { return write((uint8_t)n); }
    inline size_t write(int n) { return write((uint8_t)n); }
    using Print::write;
	
	operator bool() 
                 {  delay(2000);  
                    return true; 
                  }
    struct usart_dev* c_dev(void) { return this->usart_device; }
private:
    struct usart_dev *usart_device;
    uint8_t tx_pin;
    uint8_t rx_pin;
};

extern USBSerial Serial;

#endif

