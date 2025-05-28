
#include "uart.h"
#include "usart.h"
#include "gpio.h"
#include "stdutils.h"
#include "lpc17xx.h"
#include <inttypes.h>
#include "HardwareSerial.h"
#include "Arduino.h"


extern usart_channel_map USART_BASE[4]; //Defined in UART.c file




void usart0_IRQHandler(void);
void usart1_IRQHandler(void);
void usart2_IRQHandler(void);
void usart3_IRQHandler(void);


static usart_dev usart0 = {
    .channel     = &USART_BASE[0],
    .baud_rate = 0,
    .max_baud = 4500000UL,
    .irq_NUM = UART0_IRQn,
    .userFunction = usart0_IRQHandler,
};
usart_dev *USART0 = &usart0;




static usart_dev usart1 = {
    .channel     = &USART_BASE[1],
    .baud_rate = 0,
    .max_baud = 4500001UL,
    .irq_NUM = UART1_IRQn,
    .userFunction = usart1_IRQHandler,
};
usart_dev *USART1 = &usart1;




static usart_dev usart2 = {
    .channel     = &USART_BASE[2],
    .baud_rate = 0,
    .max_baud = 2250001UL,
    .irq_NUM = UART2_IRQn,
    .userFunction = usart2_IRQHandler,
};
usart_dev *USART2 = &usart2;




static usart_dev usart3 = {
    .channel     = &USART_BASE[3],
    .baud_rate = 0,
    .max_baud = 2250002UL,
    .irq_NUM = UART3_IRQn,
    .userFunction = usart3_IRQHandler,
};
usart_dev *USART3 = &usart3;




 
void usart_init(usart_dev *dev) {
  uint32_t usartPclk,pclk,RegValue;
          
        
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
         dev->channel->UARTx->IER = 0x01; // Enable Rx  interrupt     
         NVIC_EnableIRQ(dev->irq_NUM);          
}




void usart_enable(usart_dev *dev) {

}


void usart_disable(usart_dev *dev) {

}



uint32_t usart_tx(usart_dev *dev, const uint8_t *buf, uint32_t len) {
    usart_channel_map *regs = dev->channel;
    uint32_t txed = 0;
    while ((util_IsBitCleared(regs->UARTx->LSR,SBIT_THRE)) && (txed < len)) {
        regs->UARTx->THR = buf[txed++];
    }
    return txed;
}


 
 

/**
 * @return Number of bytes received
 */
 
unsigned int usart_rx_available(usart_dev *dev) 
{
    return ((dev->rx_buf_head -dev->rx_buf_tail) & USART_BUF_SIZE_MASK );
}

char usart_getc(usart_dev *dev)
{
    char ch;

 
   if (dev->rx_buf_head == dev->rx_buf_tail) 
   {
    ch = -1;
    }
    else 
    {
       ch = dev->rx_buf[dev->rx_buf_tail];
       dev->rx_buf_tail = (dev->rx_buf_tail + 1) & USART_BUF_SIZE_MASK;
    }
   
   return ch;
} 

int usart_peek(usart_dev *dev)
{
  if (dev->rx_buf_head == dev->rx_buf_tail) 
  {
    return -1;
  } 
  else 
  {
    return dev->rx_buf[dev->rx_buf_tail];
  }
}

uint32_t usart_rx(usart_dev *dev, uint8_t *buf, uint32_t len) {
    uint32_t rxed = 0;
  

 
  while (rxed < len) {
        *buf++ = usart_getc(dev);
        rxed++;
    }   

    return rxed;
}



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



/***************************************************************************************************
                            USART IRQ call backs
****************************************************************************************************
  Actual UART ISRs are in uart.c file.
                                 
****************************************************************************************************/
#define IIR_RDA		0x04
#define IIR_THRE	0x02
#define LSR_THRE    0x10
#define LSR_RDR     0x01

void usart0_IRQHandler(void)
{
  uint32_t iir_reg,lsr_reg;
  uint8_t uart_data, temp_head;
	
 
  iir_reg = LPC_UART0->IIR & 0x0f;

  lsr_reg = LPC_UART0->LSR; 
  
  if(iir_reg == IIR_RDA)
  {
      if(lsr_reg & LSR_RDR)
      {
      uart_data = LPC_UART0->RBR;
      temp_head = (USART0->rx_buf_head + 1) & USART_BUF_SIZE_MASK;
      
      if(temp_head != USART0->rx_buf_tail )
      {
          USART0->rx_buf[USART0->rx_buf_head] = uart_data;
          USART0->rx_buf_head = temp_head;
      }
      }     
  }  
}


 

void usart1_IRQHandler(void)
{
   uint32_t iir_reg,lsr_reg;
  uint8_t uart_data, temp_head;
	
 
  iir_reg = LPC_UART1->IIR & 0x0f;

  lsr_reg = LPC_UART1->LSR; 
  
  if(iir_reg == IIR_RDA)
  {
      if(lsr_reg & LSR_RDR)
      {
      uart_data = LPC_UART1->RBR;
      temp_head = (USART1->rx_buf_head + 1) & USART_BUF_SIZE_MASK;
      
      if(temp_head != USART1->rx_buf_tail )
      {
          USART1->rx_buf[USART1->rx_buf_head] = uart_data;
          USART1->rx_buf_head = temp_head;
      }
      }     
  } 
}


void usart2_IRQHandler(void)
{
   uint32_t iir_reg,lsr_reg;
  uint8_t uart_data, temp_head;
	
 
  iir_reg = LPC_UART2->IIR & 0x0f;

  lsr_reg = LPC_UART2->LSR; 
  
  if(iir_reg == IIR_RDA)
  {
      if(lsr_reg & LSR_RDR)
      {
      uart_data = LPC_UART2->RBR;
      temp_head = (USART2->rx_buf_head + 1) & USART_BUF_SIZE_MASK;
      
      if(temp_head != USART2->rx_buf_tail )
      {
          USART2->rx_buf[USART2->rx_buf_head] = uart_data;
          USART2->rx_buf_head = temp_head;
      }
      }     
  } 
}


void usart3_IRQHandler(void)
{
  uint32_t iir_reg,lsr_reg;
  uint8_t uart_data, temp_head;
	
 
  iir_reg = LPC_UART3->IIR & 0x0f;

  lsr_reg = LPC_UART3->LSR; 
  
  if(iir_reg == IIR_RDA)
  {
      if(lsr_reg & LSR_RDR)
      {
      uart_data = LPC_UART3->RBR;
      temp_head = (USART3->rx_buf_head + 1) & USART_BUF_SIZE_MASK;
      
      if(temp_head != USART3->rx_buf_tail )
      {
          USART3->rx_buf[USART3->rx_buf_head] = uart_data;
          USART3->rx_buf_head = temp_head;
      }
      }     
  } 
}
/*************************************************************************************************
                                    END of  ISR's 
*************************************************************************************************/



HardwareSerial Serial0(USART0); 
HardwareSerial Serial1(USART1); 
HardwareSerial Serial2(USART2); 
HardwareSerial Serial3(USART3); 
