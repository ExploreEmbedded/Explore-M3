/***************************************************************************************************
                                ExploreEmbedded    
****************************************************************************************************
* File:   spiIntr.h
* Version: 16.0
* Author: ExploreEmbedded
* Website: http://www.exploreembedded.com/wiki
* Description: File contains the function declaration and the SFR bit number for configuring and using the LPC1768 timers.
                

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
#ifdef __cplusplus
extern "C" {
#endif 

#ifndef _SPIINTR_H_
#define _SPIINTR_H_

#include "lpc17xx.h"

/*************************************************************************************************
                        SFR Bits of timers registers							   
**************************************************************************************************/
/* Power Control for Peripherals register */
#define SBIT_PCONP_PCSPI    9
#define SBIT_PCONP_PCSSP1  10

/* Peripheral Clock Selection register 0 */
#define SBIT_PCLKSEL0_PCLK_SPI   16
#define SBIT_PCLKSEL0_PCLK_SSP1  20

/* SSP Interrupt Mask Set/Clear register */
#define SBIT_SSPIMSC_RORIM	(1 << 0)
#define SBIT_SSPIMSC_RTIM	(1 << 1)
#define SBIT_SSPIMSC_RXIM	(1 << 2)
#define SBIT_SSPIMSC_TXIM	(1 << 3)

/* SSP0 Interrupt Status register */
#define SBIT_SSPRIS_RORRIS	(1 << 0)
#define SBIT_SSPRIS_RTRIS	(1 << 1)
#define SBIT_SSPRIS_RXRIS	(1 << 2)
#define SBIT_SSPRIS_TXRIS	(1 << 3)

/* SSP0 Masked Interrupt register */
#define SBIT_SSPMIS_RORMIS	(1 << 0)
#define SBIT_SSPMIS_RTMIS	(1 << 1)
#define SBIT_SSPMIS_RXMIS	(1 << 2)
#define SBIT_SSPMIS_TXMIS	(1 << 3)

/* SSP0 Interrupt clear register */
#define SBIT_SSPICR_RORIC	(1 << 0)
#define SBIT_SSPICR_RTIC	(1 << 1)


#define SBIT_SSPSR_RNE     (1 << 2)

/*************************************************************************************************/





/*************************************************************************************************
                        Costants, Structures and Typedefs for timers 							   
**************************************************************************************************/
#define RING_BUFFER_SIZE 256

typedef enum
{
    SPI_0,
    SSP_1,
    SPI_MAX,
} SPI_ENUM;

typedef void (*voidFuncPtr)(void);

typedef struct
{
    voidFuncPtr userFunction;
    LPC_SSP_TypeDef *SSPx;
    IRQn_Type IrqNumber;
    uint8_t pconBits;
    uint8_t pclkBits;  
}spi_dev;



/*************************************************************************************************/




/*************************************************************************************************
                                Function Prototypes 							   
*************************************************************************************************/
spi_dev *SPI_Init(uint8_t spiNumber_u8);     
uint8_t readRecevBuff(uint8_t *buff, uint8_t length);
uint16_t bufferAvailable(void);
uint8_t* readBuff(void);

/*************************************************************************************************/

#endif

#ifdef __cplusplus
}
#endif


