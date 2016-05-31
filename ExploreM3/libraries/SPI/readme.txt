Explore M3 supports two Hardware SPI's 0,1.
By default SPI1 is mapped to SPI libarary (spi.cpp-> SPIClass SPI(1)).
Both the hardware SPI's can be used simulaneouls by creating two instances of class.

SPI0: The SPI0 lines are shared with UART1. Hence the Serial1 needs to be disabled in usart.cpp file for usig SPI0.
 MOSI   pin 9    pin 10
 MISO   pin 8    pin 11
 CLK    pin 7    pin 12
 CS     pin 6    pin 13 
 
 
SPI1: 
 MOSI  pin 10
 MISO  pin 11
 CLK   pin 12
 CS    pin 13  
 