/***************************************************************************************************
                                   ExploreEmbedded    
****************************************************************************************************
 * File:   timer.h
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
#ifndef _HARDWARE_TIMERS_H_
#define _HARDWARE_TIMERS_H_


#include "lpc17xx.h"
#include "timer.h"











/*************************************************************************************************
                         Costants, Structures and Typedefs for timers 							   
**************************************************************************************************/
/* #define TIMER_0     0
#define TIMER_1     1
#define TIMER_2     2
#define TIMER_3     3
#define TIMER_MAX   4

typedef void (*voidFuncPtr)(void);

typedef struct
{
    voidFuncPtr userFunction;
    LPC_TIM_TypeDef *TIMx;
    IRQn_Type IrqNumber;
    uint8_t pconBits;
    uint8_t pclkBits;  
}timer_dev; */

/*************************************************************************************************/





class HardwareTimer {
private:
    timer_dev *dev;

public:
    /**
     * @brief Construct a new HardwareTimer instance.
     * @param timerNum number of the timer to control.
     */
    HardwareTimer(uint8_t timerNum);

    /**
     * @brief Stop the counter, without affecting its configuration.
     *
     * @see HardwareTimer::resume()
     */
    void start(void);

    /**
     * @brief Resume a paused timer, without affecting its configuration.
     *
     * The timer will resume counting and firing interrupts as
     * appropriate.
     *
     * Note that there is some function call overhead associated with
     * using this method, so using it in concert with
     * HardwareTimer::pause() is not a robust way to align multiple
     * timers to the same count value.
     *
     * @see HardwareTimer::pause()
     */
    void stop(void);


    /**
     * @brief Get the current timer count.
     *
     * @return The timer's current count value
     */
    uint32_t getCount(void);

    /**
     * @brief Set the timer's period in microseconds.
     *
     * Configures the prescaler and overflow values to generate a timer
     * reload with a period as close to the given number of
     * microseconds as possible.
     *
     * @param microseconds The desired period of the timer.  This must be
     *                     greater than zero.
     * @return none.
     */
    void setPeriod(uint32_t microseconds);

    /**
     * @brief Retruns the configured timer period in usec
     */
    //void setMode(int channel, timer_mode mode);

    /**
     * @brief Get the compare value for the given channel.
     * @see HardwareTimer::setCompare()
     */
    uint32_t getPeriod(void);


    /**
     * @brief Attach an interrupt handler to the given channel.
     *
     * This interrupt handler will be called when the timer's counter
     * reaches the given channel compare value.
     *
     * @param channel the channel to attach the ISR to, from 1 to 4.
     * @param handler The ISR to attach to the given channel.
     * @see voidFuncPtr
     */
    void attachInterrupt(voidFuncPtr handler);

    /**
     * @brief Remove the interrupt handler attached to the given
     *        channel, if any.
     *
     * The handler will no longer be called by this timer.
     *
     * @param channel the channel whose interrupt to detach, from 1 to 4.
     * @see HardwareTimer::attachInterrupt()
     */
    void detachInterrupt();

    /**
     * @brief Reset the counter, and update the prescaler and overflow
     *        values.
     *
     * This will reset the counter to 0 in upcounting mode (the
     * default).  It will also update the timer's prescaler and
     * overflow, if you have set them up to be changed using
     * HardwareTimer::setPrescaleFactor() or
     * HardwareTimer::setOverflow().
     *
     * @see HardwareTimer::setPrescaleFactor()
     * @see HardwareTimer::setOverflow()
     */
     
  
};
    


#endif
