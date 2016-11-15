
#ifdef __cplusplus
 extern "C" {
#endif 

#ifndef _EXPLORE_M3_USART_H_
#define _EXPLORE_M3_USART_H_



#include "stdint.h"
#include "lpc17xx.h"
#include "gpio.h"




typedef struct
{ 
  gpioPins_et TxPin;
  gpioPins_et RxPin;
  uint8_t PinFunSel;
  uint8_t pconBit;
  LPC_UART_TypeDef *UARTx;
}usart_channel_map;




#ifndef USART_BUF_SIZE
#define USART_BUF_SIZE               256
#define USART_BUF_SIZE_MASK          255
#endif
typedef void (*voidFuncPtr)(void);

typedef struct usart_dev {
    usart_channel_map *channel;             /*LPC1768 UART Channel Register Mapping */
    uint32_t baud_rate;
    uint32_t max_baud;               
    IRQn_Type irq_NUM;  
    voidFuncPtr  userFunction;      // ISR call back function
    uint8_t rx_buf[USART_BUF_SIZE]; 
    uint8_t tx_buf[USART_BUF_SIZE]; 
    uint8_t rx_buf_head; 
    uint8_t rx_buf_tail;     
    uint8_t tx_buf_head; 
    uint8_t tx_buf_tail;    
    uint8_t first_write;    

    
} usart_dev;

void usart_init(usart_dev *dev);

extern usart_dev *USART0;
extern usart_dev *USART1;
extern usart_dev *USART2;
extern usart_dev *USART3;


void usart_set_baud_rate(usart_dev *dev, uint32_t clock_speed, uint32_t baud);

void usart_enable(usart_dev *dev);
void usart_disable(usart_dev *dev);
void usart_foreach(void (*fn)(usart_dev *dev));
uint32_t usart_tx(usart_dev *dev, const uint8_t *buf, uint32_t len);
uint32_t usart_rx(usart_dev *dev, uint8_t *buf, uint32_t len);
void usart_putudec(usart_dev *dev, uint32_t val);
void usart_putc(usart_dev *dev, char ch);
char usart_getc(usart_dev *dev);
unsigned int usart_rx_available(usart_dev *dev);
int usart_peek(usart_dev *dev);




#endif

#ifdef __cplusplus
}
#endif
