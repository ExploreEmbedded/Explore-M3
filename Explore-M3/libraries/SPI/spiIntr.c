/***************************************************************************************************
                                ExploreEmbedded    
****************************************************************************************************
* File:   spiIntr.c
* Version: 16.0
* Author: ExploreEmbedded
* Website: http://www.exploreembedded.com/wiki
* Description: File contains the functions for configuring and using the LPC1768 timers.
                

The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the 
library works on any of development boards for respective controllers. However, ExploreEmbedded 
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information 
related to updates. 


GNU GENERAL PUBLIC LICENSE: 
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. 

Errors and omissions should be reported to codelibraries@exploreembedded.com
**************************************************************************************************/

#include "lpc17xx.h"
#include "spiIntr.h"
#include "stdutils.h"


/**************************************************************************************************
                    SPI configuration table(Do not alter uncless required)
**************************************************************************************************/
spi_dev spi_dev_Table[SPI_MAX] = 
{/* userFunPtr              SPI Struct           IRQ Number       PCONP bit         pclkBit    */
    { NULL,                                NULL,  SPI_IRQn,     SBIT_PCONP_PCSPI,  SBIT_PCLKSEL0_PCLK_SPI, },
    { NULL,    (LPC_SSP_TypeDef *)LPC_SSP1_BASE, SSP1_IRQn,    SBIT_PCONP_PCSSP1, SBIT_PCLKSEL0_PCLK_SSP1, },
};
/*************************************************************************************************/

uint16_t ring_buffer_head;
uint16_t ring_buffer_tail;
uint8_t ring_buffer[RING_BUFFER_SIZE]; 

/*************************************************************************************************
                    Local function declaration
**************************************************************************************************/
uint32_t getPrescalarForUs(uint8_t spiPclkBit_u8);
uint8_t bufferRead(void);
void bufferWrite(uint8_t dataPoint);

/*************************************************************************************************/




/***************************************************************************************************
            spi_dev *SPI_Init(uint8_t timerNumber_u8)
****************************************************************************************************
* I/P Arguments: 
                uint8_t: Timer number(TIMER0-TIMER3) that needs to be initialized.
                uint32_t: Timer tick value, Delay time in us.


* Return value: none

* description :This function initializes the timer with specfied delay.
                The requested timer should be within rage(TIMER_0,TIMER_3).
                The delay time is multiple of uSec.

##Note: This function will only initialize the timers with required delay.
        TIMER_Start() fuctions needs to be called to start the timer.                                  
****************************************************************************************************/
spi_dev *SPI_Init(uint8_t spiNumber_u8)
{         
    LPC_SC->PCONP |= ((uint32_t)1<<spi_dev_Table[spiNumber_u8].pconBits); /* Power ON Timer0,1 */

    ring_buffer_head = 0;
    ring_buffer_tail = 0;
    
    return (&spi_dev_Table[spiNumber_u8]);
}



/***************************************************************************************************
                            SPI_ISR's
****************************************************************************************************
desc: The four ISR's will be called independently whenever the configured delay time is elapsed.
    In other words the ISR's will be called when the Timer Count(TC) reaches the Match Value(MR0).
                
    The ISR will clear the Interrupt bit as it is being served.(Setting the bit will clear the Corresponding ISR Bit)
    If the user CallBack Function is configured then it will be called. 
                                
****************************************************************************************************/
void SPI0_IRQHandler(void)
{

}


void SSP1_IRQHandler(void)
{
    uint32_t regValue;

    regValue = LPC_SSP1->MIS;
    if ( regValue & SBIT_SSPMIS_RORMIS )	/* Receive overrun interrupt */
    {
        LPC_SSP1->ICR = SBIT_SSPICR_RORIC;		/* clear interrupt */
    }
    if ( regValue & SBIT_SSPMIS_RTMIS )	/* Receive timeout interrupt */
    {
        LPC_SSP1->ICR = SBIT_SSPICR_RTIC;		/* clear interrupt */
    }

    if ( regValue & SBIT_SSPMIS_RXMIS )	/* Rx at least half full */
    {
        /* receive until it's empty */	
        while(SBIT_SSPSR_RNE & LPC_SSP1->SR)    
        {
            bufferWrite(LPC_SSP1->DR);
        }    
    }

    
    if((spi_dev_Table[SSP_1].userFunction!=NULL) && (bufferAvailable()))
    {
        spi_dev_Table[SSP_1].userFunction();
    }
}

/*************************************************************************************************
                                    END of  ISR's 
*************************************************************************************************/

uint8_t bufferRead(void)
{
    uint8_t dataPoint;

    if (ring_buffer_head == ring_buffer_tail) 
    {// if the head isn't ahead of the tail, we don't have any characters
        dataPoint = 0;
    } 
    else 
    {
        dataPoint = ring_buffer[ring_buffer_tail];
        ring_buffer_tail = (ring_buffer_tail + 1) % RING_BUFFER_SIZE;
    }
    return dataPoint;
} // read

void bufferWrite(uint8_t dataPoint)
{  
    uint16_t index = (ring_buffer_head + 1) % RING_BUFFER_SIZE;
    
    if((index != ring_buffer_tail)) 
    {
        ring_buffer[ring_buffer_head] = dataPoint;
        ring_buffer_head = index;
    }    
} // write

uint16_t bufferAvailable(void)
{
    return ((uint16_t)(RING_BUFFER_SIZE + ring_buffer_head - ring_buffer_tail)) % RING_BUFFER_SIZE;
} // available


uint8_t readRecevBuff(uint8_t *buff, uint8_t length)
{
    uint8_t readBytes = bufferAvailable();
    readBytes = readBytes < length ? readBytes : length;
    memcpy(buff, ring_buffer, readBytes);
    
    return (readBytes);
}



uint8_t* readBuff(void)
{   
   return (ring_buffer);
}


/***************************************************************************************************
            uint32_t getPrescalarForUs(uint8_t spiPclkBit_u8)
****************************************************************************************************
* I/P Arguments: 
                uint8_t: Start bit of the timer in PCLKSELx register.
                        Refer data sheet for more info on PCLKSEL0/PCLKSEL1 registers

* Return value: 
            uint32_t: Prescalar counter value for 1us. 

* description :
                This functions calculates the prescalar value for 1us for the requested timer.
                It first gets the pclk bit info from PCLKSELx registers.
                Later the bits are decoded to get the peripheral clock value.
                Finally the pclk is divided by 1000000 to get the prescalar count for 1us.                
****************************************************************************************************/
uint32_t getPrescalarForUs(uint8_t spiPclkBit_u8)
{
    uint32_t pclk,prescalarForUs;
    pclk = (LPC_SC->PCLKSEL0 >> spiPclkBit_u8) & 0x03;  /* get the pclk info for required ssp1 */

    switch ( pclk )                                    /* Decode the bits to determine the pclk*/
    {
    case 0x00:
        pclk = SystemCoreClock/4;
        break;

    case 0x01:
        pclk = SystemCoreClock;
        break; 

    case 0x02:
        pclk = SystemCoreClock/2;
        break; 

    case 0x03:
        pclk = SystemCoreClock/8;
        break;
    }

    prescalarForUs =pclk/1000000 - 1;                      /* Prescalar for 1us (1000000Counts/sec) */

    return prescalarForUs;
}
