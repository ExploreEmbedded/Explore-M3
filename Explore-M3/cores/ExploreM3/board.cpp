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
    P1_9,     /* 32 */
    P1_31,    /* 33 *//* A4 */
    P0_26,    /* 34 *//* A3 */
    P0_25,    /* 35 *//* A2 */
    P0_24,    /* 36 *//* A1 */
    P0_23,    /* 37 *//* A0 */
    P1_0 ,    /* 38 RGB_RED */
    P1_1 ,    /* 39 RGB_GREEN */
    P1_4 ,    /* 40 RGB_BLUE */
    P2_11     /* 41 USB_BOOT_SWITCH */
};




 

