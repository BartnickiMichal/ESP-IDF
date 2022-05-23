#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"

#include "lwip/err.h"
#include "lwip/sys.h"

#define EXAMPLE_ESP_WIFI_SSID      "Wokwi-GUEST"
#define EXAMPLE_ESP_WIFI_PASS      ""
#define EXAMPLE_ESP_WIFI_CHN       6
#define EXAMPLE_ESP_MAXIMUM_RETRY  10
#define ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD WIFI_AUTH_OPEN

void wifi_init()
{
wifi_init_config_t wifiInitializationConfig = WIFI_INIT_CONFIG_DEFAULT(); //default config wifi
 esp_wifi_init(&wifiInitializationConfig);
 esp_wifi_set_storage(WIFI_STORAGE_RAM);  //  all configuration in ram 
 esp_wifi_set_mode(WIFI_MODE_AP); //set the mode to soft AP
  wifi_config_t wifi_config = {
        .sta = {
            {.ssid = EXAMPLE_ESP_WIFI_SSID},
            {.password = EXAMPLE_ESP_WIFI_PASS}
        },
    };
  wifi_config_t ap_config = {
          .ap = {
            .channel = EXAMPLE_ESP_WIFI_CHN ,
            .authmode = ESP_WIFI_SCAN_AUTH_MODE_THRESHOLD,
            .ssid_hidden = 0,
            .max_connection = 1,
            .beacon_interval = EXAMPLE_ESP_MAXIMUM_RETRY 
          }
        };

    esp_wifi_set_config(WIFI_IF_AP, &ap_config);
    esp_wifi_set_config(WIFI_IF_AP, &wifi_config);
    esp_wifi_start();

}


extern "C"  void app_main(void)
{
 
wifi_init();


}
