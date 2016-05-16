/***************************************************************************************************
									ExploreEmbedded
****************************************************************************************************
 * File: RTOS_11_mutex.ino
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description: Program to demonstrate the mutex usage and priority inheritance


The libraries have been tested on ExploreEmbedded development boards. We strongly believe that the
library works on any of development boards for respective controllers. However, ExploreEmbedded
disclaims any kind of hardware failure resulting out of usage of libraries, directly or indirectly.
Files may be subject to change without prior notice. The revision history contains the information
related to updates.


GNU GENERAL PUBLIC LICENSE:
	   This program is free software: you can redistribute it and/or modify
	   it under the terms of the GNU General Public License as published by
	   the Free Software Foundation, either version 3 of the License, or
	  (at your option) any later version.

	   This program is distributed in the hope that it will be useful,
	   but WITHOUT ANY WARRANTY; without even the implied warranty of
	   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
	   GNU General Public License for more details.

	   You should have received a copy of the GNU General Public License
	   along with this program. If not, see <http://www.gnu.org/licenses/>.

Errors and omissions should be reported to codelibraries@exploreembedded.com
 **************************************************************************************************/

/* Scheduler include files. */
#include <FreeRtOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <croutine.h>
#include <semphr.h>

xTaskHandle LPT_Handle;
xTaskHandle MPT_Handle;
xTaskHandle HPT_Handle;

xSemaphoreHandle xSemaphore = NULL;

#define LED_My_LPT P2_0
#define LED_My_MPT P2_1
#define LED_My_HPT P2_2

void setup()
{
  // put your setup code here, to run once:

  pinMode(LED_My_LPT, OUTPUT);
  pinMode(LED_My_MPT, OUTPUT);
  pinMode(LED_My_HPT, OUTPUT);

  /* Initialize the Serial communication module */
  Serial0.begin(38400);

  xSemaphore = xSemaphoreCreateMutex();		/* Create Mutex */

  if(xSemaphore != NULL)
  {
    Serial0.printf("\n\r\n\nSemaphore successfully created, Creating low priority task");
    xTaskCreate(My_LPT, "LowTask", configMINIMAL_STACK_SIZE, NULL, 1, &LPT_Handle);
    vTaskStartScheduler();
  }
  else
    Serial0.printf("\n\rFailed to create Semaphore");

}

void loop()
{
  // put your main code here, to run repeatedly:
}

static void My_LPT(void* pvParameters)
{
  unsigned char LowPrio;

  LED_Glow(LED_My_LPT);	 /* Led to indicate the execution of My_LPT*/

  LowPrio = uxTaskPriorityGet(LPT_Handle);
  Serial0.printf("\n\rLPT:%d,Acquiring semaphore", LowPrio);

  xSemaphoreTake(xSemaphore, portMAX_DELAY);

  Serial0.printf("\n\rLPT: Creating HPT");
  xTaskCreate(My_HPT, "HighTask", configMINIMAL_STACK_SIZE, NULL, 3, &HPT_Handle);

  LED_Glow(LED_My_LPT);	 /* Led to indicate the execution of My_LPT*/
  LowPrio = uxTaskPriorityGet(LPT_Handle);
  Serial0.printf("\n\rLPT:%d Creating MPT", LowPrio);
  xTaskCreate(My_MPT, "MidTask", configMINIMAL_STACK_SIZE, NULL, 2, &MPT_Handle);

  LED_Glow(LED_My_LPT);	 /* Led to indicate the execution of My_LPT*/
  LowPrio = uxTaskPriorityGet(LPT_Handle);
  Serial0.printf("\n\rLPT:%d Releasing Semaphore", LowPrio);
  xSemaphoreGive(xSemaphore);

  LED_Glow(LED_My_LPT);	 /* Led to indicate the execution of My_LPT*/
  LowPrio = uxTaskPriorityGet(LPT_Handle);
  Serial0.printf("\n\rFinally Exiting LPT:%d", LowPrio);
  vTaskDelete(LPT_Handle);

}


static void My_MPT(void* pvParameters)
{
  uint8_t MidPrio;

  LED_Glow(LED_My_MPT);	 /* Led to indicate the execution of My_MPT*/
  MidPrio = uxTaskPriorityGet(MPT_Handle);

  Serial0.printf("\n\rIn MPT:%d", MidPrio);

  vTaskDelete(MPT_Handle);
}


static void My_HPT(void* pvParameters)
{
  uint8_t HighPrio;

  LED_Glow(LED_My_HPT);	 /* Led to indicate the execution of My_HPT*/
  HighPrio = uxTaskPriorityGet(HPT_Handle);
  Serial0.printf("\n\rIn HPT:%d, trying to Acquire the semaphore", HighPrio);

  HighPrio = uxTaskPriorityGet(HPT_Handle);
  xSemaphoreTake(xSemaphore, portMAX_DELAY);
  LED_Glow(LED_My_HPT);	 /* Led to indicate the execution of My_HPT*/
  Serial0.printf("\n\rIn HPT:%d, Acquired the semaphore", HighPrio);

  HighPrio = uxTaskPriorityGet(HPT_Handle);
  Serial0.printf("\n\rIn HPT:%d, releasing the semaphore", HighPrio);
  xSemaphoreGive(xSemaphore);

  Serial0.printf("\n\rExiting the HPT");
  vTaskDelete(HPT_Handle);
}


static void LED_Glow(int LED)
{

  digitalWrite(LED_My_LPT, LOW);
  digitalWrite(LED_My_MPT, LOW);
  digitalWrite(LED_My_HPT, LOW);

  switch(LED)
  {
    case LED_My_LPT:
      digitalWrite(LED_My_LPT, HIGH);
      break;
    case LED_My_MPT:
      digitalWrite(LED_My_MPT, HIGH);
      break;
    case LED_My_HPT:
      digitalWrite(LED_My_HPT, HIGH);
      break;
    default :
      break;
  }
}
