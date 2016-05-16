/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   timer.c
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
#include "timer.h"
#include "stdutils.h"
#include "uart.h"



/**************************************************************************************************
                      Timer configuration table(Do not alter uncless required)
**************************************************************************************************/
timer_dev timer_dev_Table[TIMER_MAX] = 
{/* userFunPtr              Timer Struct        IRQ Number       PCONP bit    pclkBit    */
   { NULL,    (LPC_TIM_TypeDef *)LPC_TIM0_BASE, TIMER0_IRQn,    SBIT_PCTIM0, PCLK_TIMER0, },
   { NULL,    (LPC_TIM_TypeDef *)LPC_TIM1_BASE, TIMER1_IRQn,    SBIT_PCTIM1, PCLK_TIMER0, },
   { NULL,    (LPC_TIM_TypeDef *)LPC_TIM2_BASE, TIMER2_IRQn,    SBIT_PCTIM2, PCLK_TIMER0, },
   { NULL,    (LPC_TIM_TypeDef *)LPC_TIM3_BASE, TIMER3_IRQn,    SBIT_PCTIM3, PCLK_TIMER0, },
};
/*************************************************************************************************/




/*************************************************************************************************
                       Local function declaration
**************************************************************************************************/
uint32_t getPrescalarForUs(uint8_t timerPclkBit_u8);
/*************************************************************************************************/




/***************************************************************************************************
            timer_dev *TIMER_Init(uint8_t timerNumber_u8)
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
timer_dev *TIMER_Init(uint8_t timerNumber_u8)
{         
     LPC_SC->PCONP |= ((uint32_t)1<<timer_dev_Table[timerNumber_u8].pconBits); /* Power ON Timer0,1 */

     timer_dev_Table[timerNumber_u8].TIMx->MCR  = (1<<SBIT_MR0I) | (1<<SBIT_MR0R);     /* Clear TC on MR0 match and Generate Interrupt*/
     timer_dev_Table[timerNumber_u8].TIMx->PR   = getPrescalarForUs(timer_dev_Table[timerNumber_u8].pclkBits); /* Prescalar for 1us */                                  
    
    return (&timer_dev_Table[timerNumber_u8]);
}








/***************************************************************************************************
                            TIMER_ISR's
****************************************************************************************************
 desc: The four ISR's will be called independently whenever the configured delay time is elapsed.
       In other words the ISR's will be called when the Timer Count(TC) reaches the Match Value(MR0).
                 
       The ISR will clear the Interrupt bit as it is being served.(Setting the bit will clear the Corresponding ISR Bit)
       If the user CallBack Function is configured then it will be called. 
                                 
****************************************************************************************************/
void TIMER0_IRQHandler(void)
{
    util_BitSet(LPC_TIM0->IR, TIMER_0);  /* Clear Interrupt Flag */

    if(timer_dev_Table[TIMER_0].userFunction!=NULL)
    {
        timer_dev_Table[TIMER_0].userFunction();
    }
}


void TIMER1_IRQHandler(void)
{
    util_BitSet(LPC_TIM1->IR, TIMER_1);  /* Clear Interrupt Flag */

    if(timer_dev_Table[TIMER_1].userFunction!=NULL)
    {
        timer_dev_Table[TIMER_1].userFunction();
    }
}


void TIMER2_IRQHandler(void)
{
    util_BitSet(LPC_TIM2->IR, TIMER_2);  /* Clear Interrupt Flag */

    if(timer_dev_Table[TIMER_2].userFunction!=NULL)
    {
        timer_dev_Table[TIMER_2].userFunction();
    }
}


void TIMER3_IRQHandler(void)
{
    util_BitSet(LPC_TIM3->IR, TIMER_3);  /* Clear Interrupt Flag */

   if(timer_dev_Table[TIMER_3].userFunction!=NULL)
   {
       timer_dev_Table[TIMER_3].userFunction();
   }
}
/*************************************************************************************************
                                    END of  ISR's 
*************************************************************************************************/






/***************************************************************************************************
            uint32_t getPrescalarForUs(uint8_t timerPclkBit_u8)
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
uint32_t getPrescalarForUs(uint8_t timerPclkBit_u8)
{
    uint32_t pclk,prescalarForUs;

    if(timerPclkBit_u8<=4)
    {
        pclk = (LPC_SC->PCLKSEL0 >> timerPclkBit_u8) & 0x03;  /* get the pclk info for required timer0/1 */
    }
    else
    {
        pclk = (LPC_SC->PCLKSEL1 >> timerPclkBit_u8) & 0x03;  /* get the pclk info for required timer2/3 */
    }
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
