/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2011 LeafLabs, LLC.
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
 * @file   wirish/boards/maple_mini/board.cpp
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Explore M3 board file.
 */

#include "board.h"
#include "gpio.h"
#include "stdutils.h"


/* 
 * Saheb
 * 
 * 04/03/2016
 *
 * Added the pin mapping for Explore M3 
 */	
const uint8_t PIN_MAP[BOARD_MAX_GPIO_PINS] = {
    
    P0_3 ,    /* 0 */
    P0_2 ,    /* 1 */
    P0_1 ,    /* 2 */
    P0_0 ,    /* 3 */
    P0_11,    /* 4 */
    P0_10,    /* 5 */
    P0_16,    /* 6 */
    P0_15,    /* 7 */
    P0_17,    /* 8 */
    P0_18,    /* 9 */
    P0_9 ,    /* 10 */
    P0_8 ,    /* 11 */
    P0_7 ,    /* 12 */
    P0_6 ,    /* 13 */
    P0_5 ,    /* 14 */
    P0_4 ,    /* 15 */
    P1_29,    /* 16 */
    P0_22,    /* 17 */
    P0_21,    /* 18 */
    P0_20,    /* 19 */
    P0_19,    /* 20 */
    P2_8 ,    /* 21 */
    P2_7 ,    /* 22 */
    P2_6 ,    /* 23 */
    P2_5 ,    /* 24 PWM_6 */
    P2_4 ,    /* 25 PWM_5 */
    P2_3 ,    /* 26 PWM_4 */
    P2_2 ,    /* 27 PWM_3 */
    P2_1 ,    /* 28 PWM_2 */
    P2_0 ,    /* 29 PWM_1 */
    P2_12,    /* 30 */
    P2_13,    /* 31 */
    P0_23,    /* A0 */
    P0_24,    /* A1 */
    P0_25,    /* A2 */
    P0_26,    /* A3 */
    P1_30,    /* A4 */
    P1_31,    /* A5 */ 
    P1_0 ,    /* RGB_RED */
    P1_1 ,    /* RGB_GREEN */
    P1_4      /* RGB_BLUE */            
};




/* 
 * Saheb
 * 
 * 04/03/2016
 *
 * Added the definitions for Hardware Serial devices so that each board can define which Arduino "Serial" instance
 * Maps to which hardware serial port on the microprocessor
 *
 * Note. Serial Class is mapped to VCOM(USB) on Explore M3(LPC1768). It also has 4hardware Serial ports mapped to Serial0-Serial3.  
 */							
/* DEFINE_HWSERIAL(Serial0, 0); 
DEFINE_HWSERIAL(Serial1, 1);
DEFINE_HWSERIAL(Serial2, 2);
DEFINE_HWSERIAL(Serial3, 3); */


#if 0
 usart_channel_map USART_BASE[4]=
{  /* TxPin RxPin UART_PinFun   PCON Bit Associated UART Structure    */
    { P0_2, P0_3, PINSEL_FUNC_1,  3     ,(LPC_UART_TypeDef *)LPC_UART0_BASE}, /* Configure P0_2,P0_3 for UART0 function */
    { P2_0, P2_1, PINSEL_FUNC_2,  4     ,(LPC_UART_TypeDef *)LPC_UART1_BASE}, /* Configure P2_0,P2_1 for UART1 function */
    { P0_10,P0_11,PINSEL_FUNC_1,  24    ,(LPC_UART_TypeDef *)LPC_UART2_BASE}, /* Configure P0_10,P0_11 for UART2 function */
    { P4_28,P4_29,PINSEL_FUNC_3,  25    ,(LPC_UART_TypeDef *)LPC_UART3_BASE}  /* Configure P4_28,P4_29 for UART3 function */ 
};




/* 
 * Saheb
 * 
 * 04/03/2016
 *
 * Added the pin mapping for Explore M3 ADC 
 */
const adcChannelConfig_st AdcConfig[C_MaxAdcChannels_U8]=
{
  { P0_23, PINSEL_FUNC_1}, /* AD0[0] is on P0.23 second alternative function */
  { P0_24, PINSEL_FUNC_1}, /* AD0[1] is on P0.24 second alternative function */
  { P0_25, PINSEL_FUNC_1}, /* AD0[2] is on P0.25 second alternative function */
  { P0_26, PINSEL_FUNC_1}, /* AD0[3] is on P0.26 second alternative function */
  { P1_30, PINSEL_FUNC_3}, /* AD0[4] is on P1.30 third alternative function */
  { P1_31, PINSEL_FUNC_3}, /* AD0[5] is on P1.31 third alternative function */
  { P0_3,  PINSEL_FUNC_2}, /* AD0[6] is on P0.3  third alternative function */
  { P0_2,  PINSEL_FUNC_2}  /* AD0[7] is on P0.2  third alternative function */
}; 

#endif	