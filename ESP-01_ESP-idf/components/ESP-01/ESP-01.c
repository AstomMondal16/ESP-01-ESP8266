#include "ESP-01.h"
#include "esp_log.h"
#include <string.h>

static const char *TAG = "ESP32S3_ESP-01";

void uart_init(void) {
    const uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_DEFAULT,
    };
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

void send_at_command(const char *command, int delay_ms) {
    uart_write_bytes(UART_NUM_1, command, strlen(command));
    uart_write_bytes(UART_NUM_1, "\r\n", 2);
    ESP_LOGI(TAG, "Sent: %s", command);
    vTaskDelay(pdMS_TO_TICKS(delay_ms));
}

void read_uart_response(void) {
    uint8_t data[RX_BUF_SIZE];
    int length = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE, pdMS_TO_TICKS(1000));
    if (length > 0) {
        data[length] = '\0'; // Null-terminate the received string
        ESP_LOGI(TAG, "Received: %s", data);
    }
}

void esp01_ping_task(void *arg) {
    // Test AT command
    send_at_command("AT", 1000);
    read_uart_response();

    //Retrieving the firmware version Id.
    // send_at_command("AT+GMR", 1000);
    // read_uart_response();

    // Set to STA mode
    send_at_command("AT+CWMODE=1", 1000);
    read_uart_response();

    //Retrieving the list of visible network
    // send_at_command("AT+CWLAP",1000);
    // read_uart_response();

    // Connect to Wi-Fi
    send_at_command("AT+CWJAP=\"Redmi\",\"12345678\"", 7000);
    read_uart_response();

    // Retrieve and print IP address after connecting to Wi-Fi
    send_at_command("AT+CIFSR", 1000); 
    read_uart_response();

    // Send ping command
    send_at_command("AT+PING=\"google.com\"", 2000);
    read_uart_response();

    ESP_LOGI(TAG, "Ping command sent!\n");

    //disconnect the connected network
    // send_at_command("AT+CWQAP",1000);
    // read_uart_response();

    vTaskDelete(NULL);
}