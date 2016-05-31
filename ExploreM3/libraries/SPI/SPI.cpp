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

#include "SPI.h"

SPIClass SPI(1);


#define SPI0_FUNCTION  PINSEL_FUNC_3
#define SPI1_FUNCTION  PINSEL_FUNC_2

#define SPI0_MOSI  P0_18
#define SPI0_MISO  P0_17
#define SPI0_SCK   P0_15
#define SPI0_SSEL  P0_16

#define SPI1_MOSI  P0_9
#define SPI1_MISO  P0_8
#define SPI1_SCK   P0_7
#define SPI1_SSEL  P0_6

uint32_t spi_GetPclk(void);

uint8_t dummy_u8;
uint8_t SPIClass::initialized = 0;
uint8_t SPIClass::interruptMode = 0;
uint8_t SPIClass::interruptMask = 0;
uint8_t SPIClass::interruptSave = 0;
#ifdef SPI_TRANSACTION_MISMATCH_LED
uint8_t SPIClass::inTransactionFlag = 0;
#endif

SPIClass::SPIClass(uint32_t spiPortNum)
{
    switch (spiPortNum)
    {
    case 0:
        this->spiPortNum = 0;

        GPIO_PinFunction(SPI0_SCK,SPI0_FUNCTION);   /* Configure the Pinfunctions for SPI */
        GPIO_PinFunction(SPI0_MOSI,SPI0_FUNCTION);
        GPIO_PinFunction(SPI0_MISO,SPI0_FUNCTION);

        GPIO_PinDirection(SPI0_SCK,OUTPUT);        /* Configure SCK,MOSI,SSEl as Output and MISO as Input */
        GPIO_PinDirection(SPI0_MOSI,OUTPUT);
        GPIO_PinDirection(SPI0_MISO,INPUT);
        break;


    case 1:
        this->spiPortNum = 1;
        
        GPIO_PinFunction(SPI1_SCK,SPI1_FUNCTION);   /* Configure the Pinfunctions for SPI */
        GPIO_PinFunction(SPI1_MOSI,SPI1_FUNCTION);
        GPIO_PinFunction(SPI1_MISO,SPI1_FUNCTION);
        break;

    default:
        break;
    }
}



void SPIClass::begin()
{
    //TODO: Check for beginTransaction

   uint32_t clockValue;

   switch (this->spiPortNum)
    {
    case 0:
    LPC_SPI->SPCCR = spi_GetPclk()/this->spiClock;  /* Set Spi Clock */

    LPC_SPI->SPCR = (((uint32_t)(0)<<SPI0_LSBF) | (0<<SPI0_CPHA) | (1<<SPI0_CPOL) | (1<<SPI0_MSTR));
    dummy_u8  = LPC_SPI->SPSR;               /* Dummy read to clear the flags */
    dummy_u8  = LPC_SPI->SPDR;               /* Dummy read to clear the flags */
        break;


    case 1: 
    LPC_SSP1->CR0 = (0x07) | (0<<SPI1_CPHA) | (0<<SPI1_CPOL);
    LPC_SSP1->CR1 = (1<<SPI1_SSE); 
    LPC_SSP1->CPSR = (spi_GetPclk()/this->spiClock) & 0xfE;;
        break;

    default:
        break;
    }
}



void SPIClass::beginTransaction(SPISettings settings)
{
    this->spiClock = settings.clockSetting;
    this->spiBitOrder = settings.bitOrderSetting;
    this->spiDataMode = settings.dataModeSetting;
}

void SPIClass::setBitOrder(uint8_t bitOrder)
{
    this->spiBitOrder = bitOrder;
    begin();
}



void SPIClass::setDataMode(uint8_t dataMode)
{
    this->spiDataMode = dataMode;
    begin();
}



// This function is deprecated.  New applications should use
// beginTransaction() to configure SPI settings.
void SPIClass::setClockDivider(uint32_t clockDiv)
{
    this->spiClock = clockDiv;
    begin();
}



uint8_t SPIClass::transfer(uint8_t data)
{
        switch (this->spiPortNum)
    {
    case 0:
    LPC_SPI->SPDR = data;
    while(util_GetBitStatus(LPC_SPI->SPSR,SPI0_SPIF) == 0); /* wait until data is sent */
    data = LPC_SPI->SPSR;
    data = LPC_SPI->SPDR;
        break;


    case 1:
    
    LPC_SSP1->DR = data;    
    while(LPC_SSP1->SR & (1 << 4));  // Wait until SSP is busy SPI1_BSY
    data =  LPC_SSP1->DR;
        break;

    default:
    data = 0x00;
        break;
    }
    return data;
}



void SPIClass::transfer(void *buf, size_t count)
{
    uint8_t in;
    uint8_t *p = (uint8_t *)buf;
    while (count--)
    {
        in= transfer(*p);
        *p++ = in;
    }
}



uint16_t SPIClass::transfer16(uint16_t data)
{
    union { uint16_t val; struct { uint8_t lsb; uint8_t msb; }; } in, out;
    in.val = data;
    if (this->spiBitOrder == MSBFIRST)
    {
        out.msb = transfer(in.msb);
        out.lsb = transfer(in.lsb);
    }
    else
    {
        out.lsb = transfer(in.lsb);
        out.msb = transfer(in.msb);
    }
    return out.val;
}



void SPIClass::endTransaction(void)
{
    //Do nothing
}



void SPIClass::end()
{

}



void SPIClass::usingInterrupt(uint8_t interruptNumber)
{

}



void SPIClass::notUsingInterrupt(uint8_t interruptNumber)
{

}



uint32_t spi_GetPclk(void)
{
    uint32_t v_spiPclk_u32,v_Pclk_u32;
    /**
       PCLKSELx registers contains the PCLK info for all the clock dependent peripherals.
       Bit16,Bit17 contains the SPI Clock(ie.SPI_PCLK) information.
       The SPI_PCLK and the actual Peripheral Clock(PCLK) is calculated as below.
       (Refer data sheet for more info)

       SPI_PCLK    PCLK
         0x00       SystemFreq/4
         0x01       SystemFreq
         0x02       SystemFreq/2
         0x03       SystemFreq/8
     **/

    v_spiPclk_u32 = (LPC_SC->PCLKSEL0 >> 16) & 0x03;

    switch( v_spiPclk_u32 )
    {
    case 0x00:
        v_Pclk_u32 = SystemCoreClock/4;           //SystemFrequency or  SystemCoreClock
        break;
    case 0x01:
        v_Pclk_u32 = SystemCoreClock;
        break;
    case 0x02:
        v_Pclk_u32 = SystemCoreClock/2;
        break;
    case 0x03:
        v_Pclk_u32 = SystemCoreClock/8;
        break;
    }

    return (v_Pclk_u32);
}

