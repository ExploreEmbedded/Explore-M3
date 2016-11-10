/***************************************************************************************************
                                    ExploreEmbedded Copyright Notice    
*****************************************************************************************************
 * File:   main.cpp
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: main function does the Hardware initialtization and final calls the arduino setup() and loop() functions.

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
***************************************************************************************************/
#define ARDUINO_MAIN
#include "Arduino.h"
#include "gpio.h"

#include "lpc17xx.h"
#include "stdutils.h"



extern void (*__preinit_array_start []) (void) __attribute__((weak));
extern void (*__preinit_array_end []) (void) __attribute__((weak));
extern void (*__init_array_start []) (void) __attribute__((weak));
extern void (*__init_array_end []) (void) __attribute__((weak));

#define HEAP_SIZE 1024

__attribute__ ((section(".heap")))  
unsigned char heap[HEAP_SIZE];



int main( void )
{
    
  unsigned int count;
  unsigned int i;
  
  SystemInit();
  SystemCoreClockUpdate();
  rgbInit();


  count = __preinit_array_end - __preinit_array_start;
  for (i = 0; i < count; i++)
    __preinit_array_start[i] ();

  count = __init_array_end - __init_array_start;
  for (i = 0; i < count; i++)
    __init_array_start[i] ();

  SysTick_Init();
  SysTick_Start();
  Serial.begin(9600);
  
     
	setup();

	for (;;)
	{
        loop();
    
	
	}

	return 0;
}
