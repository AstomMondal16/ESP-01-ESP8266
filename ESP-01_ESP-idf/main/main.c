#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "ESP-01.h"


void app_main(void) {
    uart_init();
    xTaskCreate(esp01_ping_task, "esp01_ping_task", 4096, NULL, 5, NULL);
}
