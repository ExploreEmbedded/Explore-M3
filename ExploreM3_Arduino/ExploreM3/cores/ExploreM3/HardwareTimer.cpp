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
#include "HardwareTimer.h"
#include "lpc17xx.h"
#include "stdutils.h"
#include "timer.h"
#include "uart.h"




HardwareTimer::HardwareTimer(uint8_t timerNum) {
    if(timerNum<TIMER_MAX)
    {
       this->dev = TIMER_Init(timerNum);  
        UART0_Init(9600);       
    }
    else
    {
        while(1);//Timer Out of range, stay here
    }
}

void HardwareTimer::start(void) {
    this->dev->TIMx->TCR  = (1 <<SBIT_CNTEN);
}

void HardwareTimer::stop(void) {
    this->dev->TIMx->TCR  = 0x00;
}


uint32_t HardwareTimer::getPeriod(void) {
    return (this->dev->TIMx->MR0);
}


void HardwareTimer::setPeriod(uint32_t microseconds) {
    
    this->dev->TIMx->MR0  = microseconds; 
    this->dev->TIMx->TC  = 0x00;  // Restart the Timer Count
}


uint32_t HardwareTimer::getCount(void) {
   return (this->dev->TIMx->TC);                 /* Load timer value to generate 100ms delay*/
}







void HardwareTimer::attachInterrupt(voidFuncPtr handler) {
        this->dev->userFunction = handler; /* Stop timer by Clearing the Counter Enable*/
        NVIC_EnableIRQ(this->dev->IrqNumber); 
}

void HardwareTimer::detachInterrupt() {
     this->dev->userFunction = NULL; /* Stop timer by Clearing the Counter Enable*/
        NVIC_DisableIRQ(this->dev->IrqNumber); 
}



/* -- Deprecated predefined instances -------------------------------------- */
//HardwareTimer Timer4(4);
//HardwareTimer Timer1(1);
//HardwareTimer Timer2(2);
//HardwareTimer Timer3(3);
