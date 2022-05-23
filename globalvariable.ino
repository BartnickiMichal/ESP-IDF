/* Multitasking Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include <pthread.h>

SemaphoreHandle_t xSemaphore;
volatile int x=0;
static int delay_arg=500;
void vATask( void * pvParameters )
{
   int delay_num=*(int*)pvParameters;

   while(1)
   {
     // xSemaphore = xSemaphoreCreateMutex();
      if( xSemaphoreTake(xSemaphore,0) == pdTRUE )
         {
             vTaskDelay(delay_num);
            x++;
            xSemaphoreGive(xSemaphore);
            printf("%d\n",x);
         }
   }
}
void vATask_second( void * pvParameters )
{
   int delay_num=*(int*)pvParameters;
   while(1)
   {
     // xSemaphore = xSemaphoreCreateMutex();
      
      if( xSemaphoreTake(xSemaphore,0) == pdTRUE )
         {
            vTaskDelay(delay_num);      
            x++;
            xSemaphoreGive(xSemaphore);
            printf("%d\n",x);
         
         }
   }
}

extern "C" void app_main()
{
  xSemaphore = xSemaphoreCreateMutex();
   xTaskCreate(&vATask, "first", 16384, (void *)&delay_arg,5,NULL);
   xTaskCreate(&vATask_second, "second", 16384, (void *)&delay_arg,5,NULL);
   
}