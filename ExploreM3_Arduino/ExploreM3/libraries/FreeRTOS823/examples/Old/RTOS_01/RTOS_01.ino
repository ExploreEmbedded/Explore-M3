#include <FreeRtOSConfig.h>
#include <FreeRTOS.h>
#include <task.h>
#include <croutine.h>




void setup()
{
  /* Initialize the Serial communication module */
  Serial.begin(9600);
  Serial.println(" In Main");

  /* Create the three tasks with priorities 1,2,3. Only tasks will be created.
  * Tasks will be excecuted once the scheduler is started.
  * An idle task is also created, which will be run when there are no tasks in RUN state */

  xTaskCreate(MyTask1, "Task1", 128, NULL, 1, NULL);
  xTaskCreate(MyTask2, "Task2", 128, NULL, 2, NULL);
  xTaskCreate(MyTask3, "Task3", 128, NULL, 3, NULL);
  xTaskCreate(MyIdleTask, "IdleTask", 128, NULL, 0, NULL);

  /* Start the schedular */
  vTaskStartScheduler();

}

void loop()
{
  // put your main code here, to run repeatedly:
      Serial.println("In idle Hook Function state");
      delay(50);
}

/* Task1 with priority 1 */
static void MyTask1(void* pvParameters)
{
  while(1)
  {
    
    Serial.println("Task1");
    vTaskDelay(100/portTICK_PERIOD_MS);
  }
}

/* Task2 with priority 2 */
static void MyTask2(void* pvParameters)
{
  while(1)
  {
    
    Serial.println("Task2");
    vTaskDelay(150/portTICK_PERIOD_MS);
  }
}

/* Task3 with priority 3 */
static void MyTask3(void* pvParameters)
{
  while(1)
  {
   
    Serial.println("Task3");
    vTaskDelay(250/portTICK_PERIOD_MS);
  }
}

/* TIdle Task with priority Zero */ 
static void MyIdleTask(void* pvParameters)
{
  while(1)
  {
   
    Serial.println("In idle state");
    delay(50);
  }
}


