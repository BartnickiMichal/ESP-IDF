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

#define LED_RED GPIO_NUM_5
#define LED_BLUE GPIO_NUM_4
#define STACK_SIZE 200

void Vblink_diode_red(void *pvParameter)
{
   while(1)
   {
      vTaskDelay(1000);
      analogWrite(LED_RED, HIGH);
      vTaskDelay(1000);
      analogWrite(LED_RED, LOW);
      
   }

}

void Vblink_diode_blue(void *pvParameter)
{
   while(1)
   {
      vTaskDelay(200);
      analogWrite(LED_BLUE, HIGH);
      vTaskDelay(200);
      analogWrite(LED_BLUE, LOW);
      
   }

}
extern "C" void app_main()
{
   xTaskCreate(&(Vblink_diode_red), "diode_red", 2048, NULL,5,NULL);
   xTaskCreate(&(Vblink_diode_blue),"diode_blue", 2048, NULL,5,NULL);
   
  
   
}