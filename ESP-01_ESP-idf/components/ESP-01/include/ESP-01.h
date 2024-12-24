#ifndef ESP01_H
#define ESP01_H

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/uart.h"

#define TXD_PIN (47)  // UART TX pin
#define RXD_PIN (48)  // UART RX pin
#define RX_BUF_SIZE 2048

void uart_init(void);
void send_at_command(const char *command, int delay_ms);
void read_uart_response(void);
void esp01_ping_task(void *arg);

#endif