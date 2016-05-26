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
 * @file   wirish/boards/maple_mini/include/board/board.h
 * @author Marti Bolivar <mbolivar@leaflabs.com>
 * @brief  Explore M3 board header.
 *
 * See wirish/boards/maple/include/board/board.h for more information
 * on these definitions.
 */
 
 #ifdef __cplusplus
extern "C" {
#endif

#ifndef _BOARD_EXPLORE_M3_H_
#define _BOARD_EXPLORE_M3_H_

#include "stdutils.h"

#define BOARD_MAX_GPIO_PINS  41
#define C_MaxAdcChannels_U8  8u

extern const uint8_t PIN_MAP[BOARD_MAX_GPIO_PINS];

#define   AA0         32
#define   A1         33
#define   A2         34
#define   A3         35
#define   A4         36
#define   A5         37
#define   RGB_RED    38
#define   RGB_BLUE   39
#define   RGB_GREEN  40
#define   PWM_1      29
#define   PWM_2      28
#define   PWM_3      27
#define   PWM_4      26
#define   PWM_5      25
#define   PWM_6      24

#define ANALOG_ZERO  AA0
#define ANALOG_MAX   A5

/* typedef struct
{ 
  gpioPins_et TxPin;
  gpioPins_et RxPin;
  uint8_t PinFunSel;
  uint8_t pconBit;
  LPC_UART_TypeDef *UARTx;
}uartChannelConfig_st;


typedef struct
{
  gpioPins_et pinNumber;
  uint8_t PinFunSel;
}adcChannelConfig_st; */


#endif


#ifdef __cplusplus
}
#endif