/*
  Copyright (c) 2011 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "variant.h"

/*
 * DUE Board pin   |  PORT  | Label
 * ----------------+--------+-------
 *   0             |  PA8   | "RX0"
 *   1             |  PA9   | "TX0"
 *   2       TIOA0 |  PB25  |
 *   3       TIOA7 |  PC28  |
 *   4       NPCS1 |  PA29  |
 *           TIOB6 |  PC26  |
 *   5       TIOA6 |  PC25  |
 *   6       PWML7 |  PC24  |
 *   7       PWML6 |  PC23  |
 *   8       PWML5 |  PC22  |
 *   9       PWML4 |  PC21  |
 *  10       NPCS0 |  PA28  |
 *           TIOB7 |  PC29  |
 *  11       TIOA8 |  PD7   |
 *  12       TIOB8 |  PD8   |
 *  13       TIOB0 |  PB27  | LED AMBER "L"
 *  14       TXD3  |  PD4   | "TX3"
 *  15       RXD3  |  PD5   | "RX3"
 *  16       TXD1  |  PA13  | "TX2"
 *  17       RXD1  |  PA12  | "RX2"
 *  18       TXD0  |  PA11  | "TX1"
 *  19       RXD0  |  PA10  | "RX1"
 *  20             |  PB12  | "SDA"
 *  21             |  PB13  | "SCL"
 *  22             |  PB26  |
 *  23             |  PA14  |
 *  24             |  PA15  |
 *  25             |  PD0   |
 *  26             |  PD1   |
 *  27             |  PD2   |
 *  28             |  PD3   |
 *  29             |  PD6   |
 *  30             |  PD9   |
 *  31             |  PA7   |
 *  32             |  PD10  |
 *  33             |  PC1   |
 *  34             |  PC2   |
 *  35             |  PC3   |
 *  36             |  PC4   |
 *  37             |  PC5   |
 *  38             |  PC6   |
 *  39             |  PC7   |
 *  40             |  PC8   |
 *  41             |  PC9   |
 *  42             |  PA19  |
 *  43             |  PA20  |
 *  44             |  PC19  |
 *  45             |  PC18  |
 *  46             |  PC17  |
 *  47             |  PC16  |
 *  48             |  PC15  |
 *  49             |  PC14  |
 *  50             |  PC13  |
 *  51             |  PC12  |
 *  52       NPCS2 |  PB21  |
 *  53             |  PB14  |
 *  54             |  PA16  | "A0"
 *  55             |  PA24  | "A1"
 *  56             |  PA23  | "A2"
 *  57             |  PA22  | "A3"
 *  58       TIOB2 |  PA6   | "A4"
 *  69             |  PA4   | "A5"
 *  60       TIOB1 |  PA3   | "A6"
 *  61       TIOA1 |  PA2   | "A7"
 *  62             |  PB17  | "A8"
 *  63             |  PB18  | "A9"
 *  64             |  PB19  | "A10"
 *  65             |  PB20  | "A11"
 *  66             |  PB15  | "DAC0"
 *  67             |  PB16  | "DAC1"
 *  68             |  PA1   | "CANRX"
 *  69             |  PA0   | "CANTX"
 *  70             |  PA17  | "SDA1"
 *  71             |  PA18  | "SCL1"
 *  72             |  PC30  | LED AMBER "RX"
 *  73             |  PA21  | LED AMBER "TX"
 *  74       MISO  |  PA25  |
 *  75       MOSI  |  PA26  |
 *  76       SCLK  |  PA27  |
 *  77       NPCS0 |  PA28  |
 *  78       NPCS3 |  PB23  | unconnected!
 *
 * USB pin         |  PORT
 * ----------------+--------
 *  ID             |  PB11
 *  VBOF           |  PB10
 *
 */


/*
 * UART objects
 */

// IT handlers
void UART_Handler(void)
{
 
}

// ----------------------------------------------------------------------------
/*
 * USART objects
 */




// IT handlers
void USART0_Handler(void)
{
 
}

void USART1_Handler(void)
{
 
}

void USART3_Handler(void)
{

}

// ----------------------------------------------------------------------------

void serialEventRun(void)
{

}

// ----------------------------------------------------------------------------




void init( void )
{

}



