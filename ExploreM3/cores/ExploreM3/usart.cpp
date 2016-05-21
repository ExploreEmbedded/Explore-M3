/******************************************************************************
 * The MIT License
 *
 * Copyright (c) 2010 Perry Hung.
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
 * @file libmaple/usart.c
 * @author Marti Bolivar <mbolivar@leaflabs.com>,
 *         Perry Hung <perry@leaflabs.com>
 * @brief Portable USART routines
 */
#include "uart.h"
#include "usart.h"
#include "gpio.h"
#include "stdutils.h"
#include "lpc17xx.h"
#include <inttypes.h>
#include "HardwareSerial.h"

/**
 * @brief Initialize a serial port.
 * @param dev         Serial port to be initialized
 */
usart_channel_map USART_BASE[4]=
{  /* TxPin RxPin UART_PinFun   PCON Bit Associated UART Structure    */
    { P0_2, P0_3, PINSEL_FUNC_1,  3     ,(LPC_UART_TypeDef *)LPC_UART0_BASE}, /* Configure P0_2,P0_3 for UART0 function */
    { P0_15, P0_16, PINSEL_FUNC_1,  4     ,(LPC_UART_TypeDef *)LPC_UART1_BASE}, /* Configure P2_0,P2_1 for UART1 function */
    { P0_10,P0_11,PINSEL_FUNC_1,  24    ,(LPC_UART_TypeDef *)LPC_UART2_BASE}, /* Configure P0_10,P0_11 for UART2 function */
    { P0_0,P0_1,PINSEL_FUNC_2,  25    ,(LPC_UART_TypeDef *)LPC_UART3_BASE}  /* Configure P4_28,P4_29 for UART3 function */ 
};






// static ring_buffer usart0_rb;
static usart_dev usart0 = {
    .channel     = &USART_BASE[0],
//    .rb       = &usart0_rb,
     .baud_rate = 0,
    .max_baud = 4500000UL,
    
 //   .clk_id   = RCC_USART0,
 //   .irq_num  = NVIC_USART0,
};
/** USART1 device */
usart_dev *USART0 = &usart0;



// static ring_buffer usart1_rb;
static usart_dev usart1 = {
    .channel     = &USART_BASE[1],
 //   .rb       = &usart1_rb,
  .baud_rate = 0,
    .max_baud = 4500001UL,
 //   .clk_id   = RCC_USART1,
 //   .irq_num  = NVIC_USART1,
};
/** USART1 device */
usart_dev *USART1 = &usart1;



//static ring_buffer usart2_rb;
static usart_dev usart2 = {
    .channel     = &USART_BASE[2],
  //  .rb       = &usart2_rb,
   .baud_rate = 0,
    .max_baud = 2250001UL,
  //  .clk_id   = RCC_USART2,
  //  .irq_num  = NVIC_USART2,
};
/** USART2 device */
usart_dev *USART2 = &usart2;

//static ring_buffer usart3_rb;
static usart_dev usart3 = {
    .channel     = &USART_BASE[3],
  //  .rb       = &usart3_rb,
   .baud_rate = 0,
    .max_baud = 2250002UL,
 //   .clk_id   = RCC_USART3,
 //   .irq_num  = NVIC_USART3,
};
/** USART3 device */
usart_dev *USART3 = &usart3;




 
void usart_init(usart_dev *dev) {
  uint32_t usartPclk,pclk,RegValue;
  
  //  rb_init(dev->rb, USART_RX_BUF_SIZE, dev->rx_buf);
   // rcc_clk_enable(dev->clk_id);
   // nvic_irq_enable(dev->irq_num);
   
    //    GPIO_PinFunction(STR_UartConfig[var_uartChannel_u8].TxPin,STR_UartConfig[var_uartChannel_u8].PinFunSel);
    //    GPIO_PinFunction(STR_UartConfig[var_uartChannel_u8].RxPin,STR_UartConfig[var_uartChannel_u8].PinFunSel);
	//	util_BitSet(LPC_SC->PCONP,STR_UartConfig[var_uartChannel_u8].pconBit);
        
        
        GPIO_PinFunction(dev->channel->TxPin,dev->channel->PinFunSel);
        GPIO_PinFunction(dev->channel->RxPin,dev->channel->PinFunSel);
		util_BitSet(LPC_SC->PCONP,dev->channel->pconBit);
        
        /* Enable FIFO and reset Rx/Tx FIFO buffers */
        dev->channel->UARTx->FCR = (1<<SBIT_FIFO) | (1<<SBIT_RxFIFO) | (1<<SBIT_TxFIFO); 

        /* 8bit data, 1Stop bit, No parity */
        dev->channel->UARTx->LCR = (0x03<<SBIT_WordLenght) | (1<<SBIT_DLAB);

        /** Baud Rate Calculation :
       PCLKSELx registers contains the PCLK info for all the clock dependent peripherals.
       Bit6,Bit7 contains the Uart Clock(ie.UART_PCLK) information.
       The UART_PCLK and the actual Peripheral Clock(PCLK) is calculated as below.
       (Refer data sheet for more info)

       UART_PCLK    PCLK
         0x00       SystemFreq/4        
         0x01       SystemFreq
         0x02       SystemFreq/2
         0x03       SystemFreq/8   
         **/

        usartPclk = (LPC_SC->PCLKSEL0 >> 6) & 0x03;

        switch( usartPclk )
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

         RegValue = ( pclk / (16 * dev->baud_rate )); 

		 dev->channel->UARTx->DLL = util_ExtractByte0to8(RegValue);
         dev->channel->UARTx->DLM = util_ExtractByte8to16(RegValue);
         
         util_BitClear(dev->channel->UARTx->LCR, SBIT_DLAB); // Clear DLAB after setting DLL,DLM        
        
}



/**
 * @brief Enable a serial port.
 *
 * USART is enabled in single buffer transmission mode, multibuffer
 * receiver mode, 8n1.
 *
 * Serial port must have a baud rate configured to work properly.
 *
 * @param dev Serial port to enable.
 * @see usart_set_baud_rate()
 */
void usart_enable(usart_dev *dev) {
 /*   usart_reg_map *regs = dev->regs;
    regs->CR1 |= (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE);// don't change the word length etc, and 'or' in the patten not overwrite |USART_CR1_M_8N1);
    regs->CR1 |= USART_CR1_UE;*/
}

/**
 * @brief Turn off a serial port.
 * @param dev Serial port to be disabled
 */
void usart_disable(usart_dev *dev) {
 #if 0   /* FIXME this misbehaves (on F1) if you try to use PWM on TX afterwards */
    usart_reg_map *regs = dev->regs;

    /* TC bit must be high before disabling the USART */
    while((regs->CR1 & USART_CR1_UE) && !(regs->SR & USART_SR_TC))
        ;

    /* Disable UE */
    regs->CR1 &= ~USART_CR1_UE;

    /* Clean up buffer */
    usart_reset_rx(dev);
    #endif
}

/**
 * @brief Nonblocking USART transmit
 * @param dev Serial port to transmit over
 * @param buf Buffer to transmit
 * @param len Maximum number of bytes to transmit
 * @return Number of bytes transmitted
 */
uint32_t usart_tx(usart_dev *dev, const uint8_t *buf, uint32_t len) {
    usart_channel_map *regs = dev->channel;
    uint32_t txed = 0;
    while ((util_IsBitCleared(regs->UARTx->LSR,SBIT_THRE)) && (txed < len)) {
        regs->UARTx->THR = buf[txed++];
    }
    return txed;
}


 
 

/**
 * @brief Nonblocking USART receive.
 * @param dev Serial port to receive bytes from
 * @param buf Buffer to store received bytes into
 * @param len Maximum number of bytes to store
 * @return Number of bytes received
 */
 
char usart_getc(usart_dev *dev)
{
    char ch;
   while(util_IsBitCleared(dev->channel->UARTx->LSR,SBIT_RDR)); 
   ch = dev->channel->UARTx->RBR; // Copy the received data
   
   return ch;
} 



uint32_t usart_rx(usart_dev *dev, uint8_t *buf, uint32_t len) {
    uint32_t rxed = 0;
  
 #if 0 
 while (usart_data_available(dev) && rxed < len) {
        *buf++ = usart_getc(dev);
        rxed++;
    }
 #endif
 
  while (rxed < len) {
        *buf++ = usart_getc(dev);
        rxed++;
    }   

    return rxed;
}

/**
 * @brief Transmit an unsigned integer to the specified serial port in
 *        decimal format.
 *
 * This function blocks until the integer's digits have been
 * completely transmitted.
 *
 * @param dev Serial port to send on
 * @param val Number to print
 */
 
void usart_putc(usart_dev *dev, char ch){
    while (util_IsBitCleared(dev->channel->UARTx->LSR,SBIT_THRE));
        dev->channel->UARTx->THR = ch; 
} 

void usart_putudec(usart_dev *dev, uint32_t val) {
    char digits[12];
    int i = 0;

    do {
        digits[i++] = val % 10 + '0';
        val /= 10;
    } while (val > 0);

    while (--i >= 0) {
        usart_putc(dev, digits[i]);
    }
}


HardwareSerial Serial0(USART0); 
HardwareSerial Serial1(USART1); 
HardwareSerial Serial2(USART2); 
HardwareSerial Serial3(USART3); 
