/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice
****************************************************************************************************
* File:   SPI.c
* Version: 15.0
* Author: ExploreEmbedded
* Website: http://www.exploreembedded.com/wiki
* Description: Contains the library function for SPI read/write

This code has been developed and tested on ExploreEmbedded boards.
We strongly believe that the library works on any of development boards for respective controllers.
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider buying the ExploreEmbedded boards.

The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION
RELATED TO UPDATES.


Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies
and that both those copyright notices and this permission notice appear in supporting documentation.
***************************************************************************************************/

#ifndef _SPI_H_INCLUDED_
#define _SPI_H_INCLUDED_

#include <Arduino.h>
#include "spiIntr.h"
#include "lpc17xx.h"


// SPI_HAS_TRANSACTION means SPI has beginTransaction(), endTransaction(),
// usingInterrupt(), and SPISetting(clock, bitOrder, dataMode)
#define SPI_HAS_TRANSACTION 1

// SPI_HAS_NOTUSINGINTERRUPT means that SPI has notUsingInterrupt() method
#define SPI_HAS_NOTUSINGINTERRUPT 1

// SPI_ATOMIC_VERSION means that SPI has atomicity fixes and what version.
// This way when there is a bug fix you can check this define to alert users
// of your code if it uses better version of this library.
// This also implies everything that SPI_HAS_TRANSACTION as documented above is
// available too.
#define SPI_ATOMIC_VERSION 1

// Uncomment this line to add detection of mismatched begin/end transactions.
// A mismatch occurs if other libraries fail to use SPI.endTransaction() for
// each SPI.beginTransaction().  Connect an LED to this pin.  The LED will turn
// on if any mismatch is ever detected.
//#define SPI_TRANSACTION_MISMATCH_LED 5

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI0_MODE_MASK   0x0C   // CPOL = bit 4, CPHA = bit 3 on SPCR
#define SSSP1_MODE_MASK  0xC0   // CPOL = bit 6, CPHA = bit 7 on SPCR
#define SPI_CLOCK_MASK   0x03   // SPR1 = bit 1, SPR0 = bit 0 on SPCR
#define SPI_2XCLOCK_MASK 0x01   // SPI2X = bit 0 on SPSR




/****************************************************************************************************
                            SPI pin numbers and pin functions
****************************************************************************************************/


#define SCK_Freq    4000000          // SPI clock frequency
/***************************************************************************************************/






/****************************************************************************************************
                            SPI SFR bits
****************************************************************************************************/
#define SPI0_CPHA    3
#define SPI0_CPOL    4
#define SPI0_MSTR    5
#define SPI0_LSBF    6
#define SPI0_SPIE    7
#define SPI0_SPIF    7


#define SPI1_CPOL    6
#define SPI1_CPHA    7
#define SPI1_SSE     1
#define SPI1_MS      2
#define SPI1_RNE     2
#define SPI1_BSY     4
/***************************************************************************************************/


class SPISettings {
public:
    SPISettings(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
        if (__builtin_constant_p(clock)) {
            init_AlwaysInline(clock, bitOrder, dataMode);
        } else {
            init_MightInline(clock, bitOrder, dataMode);
        }
    }
    SPISettings() {
        init_AlwaysInline(4000000, MSBFIRST, SPI_MODE0);
    }

private:


    void init_MightInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
        init_AlwaysInline(clock, bitOrder, dataMode);
    }
    void init_AlwaysInline(uint32_t clock, uint8_t bitOrder, uint8_t dataMode)
    __attribute__((__always_inline__))
    {
        this->clockSetting = clock;
        this->bitOrderSetting = bitOrder;
        this->dataModeSetting = dataMode;
    }
    
    uint32_t clockSetting;
    uint8_t bitOrderSetting;
    uint8_t dataModeSetting;
    friend class SPIClass;
};


class SPIClass {    
private:
    spi_dev *dev;
    
public:

    SPIClass(uint32_t spiPortNumber);
    // Initialize the SPI library
    void begin();
    void beginSlave();
    // If SPI is used from within an interrupt, this function registers
    // that interrupt with the SPI library, so beginTransaction() can
    // prevent conflicts.  The input interruptNumber is the number used
    // with attachInterrupt.  If SPI is used from a different interrupt
    // (eg, a timer), interruptNumber should be 255.
    void usingInterrupt(uint8_t interruptNumber);
    // And this does the opposite.
    void notUsingInterrupt(uint8_t interruptNumber);
    // Note: the usingInterrupt and notUsingInterrupt functions should
    // not to be called from ISR context or inside a transaction.
    // For details see:
    // https://github.com/arduino/Arduino/pull/2381
    // https://github.com/arduino/Arduino/pull/2449

    // Before using SPI.transfer() or asserting chip select pins,
    // this function is used to gain exclusive access to the SPI bus
    // and configure the correct settings.
    void beginTransaction(SPISettings settings);
    void beginTransactionSlave(SPISettings settings);

    void endTransaction(void);

    void setClockDivider(uint32_t clockDiv);
    void setBitOrder(uint8_t bitOrder);
    void setDataMode(uint8_t dataMode);
    
    uint8_t transfer(uint8_t data);
    void transfer(void *buf, size_t count);
    uint16_t transfer16(uint16_t data);

    uint16_t slaveRead(char *buf, uint8_t length);
    uint8_t* slaveRead();
    uint16_t available(void);
    
    // SPI Configuration methods
    void attachInterrupt(voidFuncPtr handler);
    void detachInterrupt(void);
    void end();

private:
    uint32_t spiPortNum;
    uint32_t spiClock;
    uint8_t spiBitOrder;
    uint8_t spiDataMode;
    uint8_t spiMasterMode;

    static uint8_t initialized;
    static uint8_t interruptMode; // 0=none, 1=mask, 2=global
    static uint8_t interruptMask; // which interrupts to mask
    static uint8_t interruptSave; // temp storage, to restore state
#ifdef SPI_TRANSACTION_MISMATCH_LED
    static uint8_t inTransactionFlag;
#endif
};

extern SPIClass SPI;

#endif
