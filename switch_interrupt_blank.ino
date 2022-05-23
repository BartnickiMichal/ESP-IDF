#include <stdio.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"

#define LED_RED GPIO_NUM_2
#define BTN_RED GPIO_NUM_13
volatile bool button_pressed = false;
void button()
{ 
    gpio_install_isr_service(0);
    gpio_reset_pin(BTN_RED);
    gpio_set_direction(BTN_RED, GPIO_MODE_INPUT);
    gpio_pullup_en(BTN_RED);
    gpio_set_intr_type(BTN_RED, GPIO_INTR_POSEDGE);
   

}
void Vblink_diode_red(void *pvParameter)
{
  while(1)
  {
  int flag=0;
  button_pressed=!(digitalRead(BTN_RED));
    if(button_pressed==true)
      {
      vTaskDelay(1000);
      analogWrite(LED_RED, HIGH);
      vTaskDelay(1000);
      analogWrite(LED_RED, LOW);
      
        while(button_pressed==true)
          {
            button_pressed=!(digitalRead(BTN_RED));
            analogWrite(LED_RED, LOW);
          }
      button_pressed=false;
      flag=1;
   
      }
      if(flag==1)
      {

        for(int i=0; i<2; i++)
        {
          vTaskDelay(1000);
          analogWrite(LED_RED, HIGH);
          vTaskDelay(1000);
          analogWrite(LED_RED, LOW);
          
        }
        flag=0;
      }
  }

}
 
extern "C" void app_main()

{  
  button();   
  xTaskCreate(&(Vblink_diode_red), "diode_red", 2048, NULL,5,NULL);
}