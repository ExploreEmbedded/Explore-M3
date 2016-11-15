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
#include "gpio.h"

#define BOARD_MAX_GPIO_PINS  42
#define C_MaxAdcChannels_U8  8u


#define EXPLORE_M3_RESET_STRING "r$T^^3"
extern const uint8_t PIN_MAP[BOARD_MAX_GPIO_PINS];

#define LED_BUILTIN 13


/************************************
             ADC pins
************************************/             
static unsigned const int A0 = 37;
static unsigned const int A1 = 36;
static unsigned const int A2 = 35;
static unsigned const int A3 = 34;
static unsigned const int A4 = 33;
//static unsigned const int A5 = 37;

#define ANALOG_ZERO  A0
#define ANALOG_MAX   A4
/**********End of ADC pins********/




/************************************
             RGB pins
************************************/             
#define   RGB_RED    38
#define   RGB_BLUE   39
#define   RGB_GREEN  40
/**********End of RGB pins**********/





/************************************
             RGB pins
************************************/             
#define   PWM_1      29
#define   PWM_2      28
#define   PWM_3      27
#define   PWM_4      26
#define   PWM_5      25
#define   PWM_6      24
/**********End of PWM pins**********/


/************************************
             SPI Pins
************************************/        
#define   SPI0_MOSI  9 
#define   SPI0_MISO  8
#define   SPI0_SCK   7
#define   SPI0_SS    6 

#define   SPI1_MOSI  10 
#define   SPI1_MISO  11
#define   SPI1_SCK   12
#define   SPI1_SS    13

//By default  the SPI1 is mapped to Arduino SPI library
#define   MOSI       SPI1_MOSI  
#define   MISO       SPI1_MISO
#define   SCK        SPI1_SCK
#define   SS         SPI1_SS
/**********End of SPI pins***********/


#define USB_BOOT_SWITCH 41

#endif


#ifdef __cplusplus
}
#endif