/***************************************************************************************************
                            ExploreEmbedded Copyright Notice    
****************************************************************************************************
 * File:   01-TaskSwitching
 * Version: 15.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: File contains the free rtos example to demonstarte the task switching.

This code has been developed and tested on ExploreEmbedded boards.  
We strongly believe that the library works on any of development boards for respective controllers. 
Check this link http://www.exploreembedded.com/wiki for awesome tutorials on 8051,PIC,AVR,ARM,Robotics,RTOS,IOT.
ExploreEmbedded invests substantial time and effort developing open source HW and SW tools, to support consider 
buying the ExploreEmbedded boards.
 
The ExploreEmbedded libraries and examples are licensed under the terms of the new-bsd license(two-clause bsd license).
See also: http://www.opensource.org/licenses/bsd-license.php

EXPLOREEMBEDDED DISCLAIMS ANY KIND OF HARDWARE FAILURE RESULTING OUT OF USAGE OF LIBRARIES, DIRECTLY OR
INDIRECTLY. FILES MAY BE SUBJECT TO CHANGE WITHOUT PRIOR NOTICE. THE REVISION HISTORY CONTAINS THE INFORMATION 
RELATED TO UPDATES.
 

Permission to use, copy, modify, and distribute this software and its documentation for any purpose
and without fee is hereby granted, provided that this copyright notices appear in all copies 
and that both those copyright notices and this permission notice appear in supporting documentation.
**************************************************************************************************/

#include <exploreM3_FreeRTOS.h>

void setup()
{
  
  Serial.begin(9600);
  Serial.println(F("In Setup function"));

  /* Create two tasks with priorities 1 and 2. An idle task is also created, 
     which will be run when there are no tasks in RUN state */

  xTaskCreate(MyTask1, "Task1", 100, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 100, NULL, 2, NULL);
  xTaskCreate(MyIdleTask, "IdleTask", 100, NULL, 0, NULL);
  vTaskStartScheduler();
}


void loop()
{
  // DO nothing
}


/* Task1 with priority 1 */
static void MyTask1(void* pvParameters)
{
  while(1)
  {
    Serial.println(F("Task1"));
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}


/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{
  while(1)
  {    
    Serial.println(F("Task2"));
    vTaskDelay(150/portTICK_PERIOD_MS);
  }
}


/* Idle Task with priority Zero */ 
static void MyIdleTask(void* pvParameters)
{
  while(1)
  {
    Serial.println(F("Idle state"));
    delay(50);
  }
}
