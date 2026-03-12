#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include "esp_log_timestamp.h"
#include "driver/uart.h"
#include "soc/uart_channel.h"
#include "log.h"

#define BUFFER_SIZE 128
#define UART_NUM UART_NUM_0
#define RX_BUFFER_SIZE (BUFFER_SIZE > UART_HW_FIFO_LEN(UART_NUM) ? BUFFER_SIZE : UART_HW_FIFO_LEN(UART_NUM) + 1)
#define TX_BUFFER_SIZE 0


void uart_log_send(const char *log_string, const size_t log_strint_lenght)
{
    if(!uart_is_driver_installed(UART_NUM))
    {
        // Configure UART parameters

        uart_config_t uart_config = {
            .baud_rate = 115200,
            .data_bits = UART_DATA_8_BITS,
            .parity = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        };  
        //Rx_buffer_size should be greater than UART_HW_FIFO_LEN(uart_num). 
        //Tx_buffer_size should be either zero or greater than UART_HW_FIFO_LEN(uart_num).
        uart_driver_install(UART_NUM, RX_BUFFER_SIZE, TX_BUFFER_SIZE, 0, NULL, 0);
        uart_param_config(UART_NUM, &uart_config);
        uart_set_pin(UART_NUM, UART_NUM_0_TXD_DIRECT_GPIO_NUM, UART_NUM_0_RXD_DIRECT_GPIO_NUM, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    }

    uart_write_bytes(UART_NUM, log_string, log_strint_lenght);
}


int log_send_message(const int LOG_LEVEL, const char *TAG, char *log_message, ...)
{
    if (TAG == NULL || log_message == NULL)
    {
        return -1;
    }
    
    char log_buffer[BUFFER_SIZE] = "";

    static const char log_level_char[] = {' ', 'F', 'E', 'W', 'I', 'D', 'T'};

    int timestamp = esp_log_early_timestamp();
    int offset = snprintf(log_buffer, BUFFER_SIZE, "[%s]-%010d-%c-", TAG, timestamp, log_level_char[LOG_LEVEL]);   
    
    if (offset >= BUFFER_SIZE)
    {
        return -1;
    }

    va_list args;
    va_start(args, log_message);
    offset += vsnprintf(log_buffer + offset, BUFFER_SIZE - offset, log_message, args);
    va_end(args);

    if (offset >= BUFFER_SIZE)
    {
        return -1;
    }

    offset += snprintf(log_buffer + offset, BUFFER_SIZE - offset, MOD_CFG_LOG_STR_END); 

    if (offset >= BUFFER_SIZE)
    {
        return -1;
    }

    uart_log_send(log_buffer, strlen(log_buffer));

    return offset;
}