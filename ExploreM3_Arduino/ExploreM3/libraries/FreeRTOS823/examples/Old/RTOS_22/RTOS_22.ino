/***************************************************************************************************
                                   ExploreEmbedded
****************************************************************************************************
 * File:   RTOS_22.ino
 * Version: 16.0
 * Author: ExploreEmbedded
 * Website: http://www.exploreembedded.com/wiki
 * Description:  Program to demonstrate the usage of queue to send and
				receive data between two tasks with some delay in Task1


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
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
		GNU General Public License for more details.

		You should have received a copy of the GNU General Public License
		along with this program.  If not, see <http://www.gnu.org/licenses/>.

Errors and omissions should be reported to codelibraries@exploreembedded.com
 **************************************************************************************************/

/* Scheduler include files. */
#include <FreeRtOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <croutine.h>
#include <queue.h>

#define MaxQueueSize 3
#define MaxElementsPerQueue 20

xTaskHandle TaskHandle_1;
xTaskHandle TaskHandle_2;

xQueueHandle MyQueueHandleId;

#define LED_Task1   P2_0
#define LED_Task2   P2_1

void setup()
{
  // put your setup code here, to run once:

  pinMode(LED_Task1, OUTPUT);
  pinMode(LED_Task2, OUTPUT);

  /* Initialize the Serial communication module */
  Serial0.begin(38400);

  MyQueueHandleId = xQueueCreate(MaxQueueSize, MaxElementsPerQueue);  /* Cretae a queue */

  if (MyQueueHandleId != 0)
  {
    Serial0.printf("\n\rQueue Created");

    xTaskCreate(MyTask1, "Task1", configMINIMAL_STACK_SIZE, NULL, 3, &TaskHandle_1);
    xTaskCreate(MyTask2, "Task2", configMINIMAL_STACK_SIZE, NULL, 2, &TaskHandle_2);

    vTaskStartScheduler();  /* start the scheduler */
  }
  else
    Serial0.printf("\n\rQueue not Created");

}

void loop()
{
  // put your main code here, to run repeatedly:
}


static void MyTask1(void* pvParameters)
{
  char RxBuffer[MaxElementsPerQueue];

  LED_Glow(LED_Task1);	  /* Led to indicate the execution of Task1*/
  Serial0.printf("\n\rTask1, Waiting for some time");
  vTaskDelay(200);

  LED_Glow(LED_Task1);	  /* Led to indicate the execution of Task1*/
  Serial0.printf("\n\rTask1, Reading the data from queue");
  if (pdTRUE == xQueueReceive(MyQueueHandleId, RxBuffer, 100))
  {
    LED_Glow(LED_Task1);	  /* Led to indicate the execution of Task1*/
    Serial0.printf("\n\rBack in task1, Received data is:%s", RxBuffer);
  }
  else
  {
    LED_Glow(LED_Task1);	  /* Led to indicate the execution of Task1*/
    Serial0.printf("\n\rBack in task1, No Data received:");
  }

  vTaskDelete(TaskHandle_1);
}


static void MyTask2(void* pvParameters)
{
  char TxBuffer[MaxElementsPerQueue] = {"Hello world"};

  LED_Glow(LED_Task2);	  /* Led to indicate the execution of Task2*/

  Serial0.printf("\n\rTask2, Filling the data onto queue");

  if (pdTRUE == xQueueSend(MyQueueHandleId, TxBuffer, 100))
  {
    LED_Glow(LED_Task2);	  /* Led to indicate the execution of Task2*/
    Serial0.printf("\n\rSuccessfully sent the data");
  }
  else
  {
    LED_Glow(LED_Task2);	  /* Led to indicate the execution of Task2*/
    Serial0.printf("\n\rSending Failed");
  }

  Serial0.printf("\n\rExiting task2");
  vTaskDelete(TaskHandle_2);
}

static void LED_Glow(int LED)
{
  digitalWrite(LED_Task1, LOW);
  digitalWrite(LED_Task2, LOW);

  switch (LED)
  {
    case LED_Task1:
      digitalWrite(LED_Task1, HIGH);
      break;
    case LED_Task2:
      digitalWrite(LED_Task2, HIGH);
      break;
    default :
      break;
  }
}
