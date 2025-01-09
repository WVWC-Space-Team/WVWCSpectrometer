#pragma once
#include "picoBoard.h"

picoBoard::picoBoard(){}

void picoBoard::init()
{
    initUART(picoBoard::uart0, 115200);
}

void picoBoard::initUART(uart_inst_t* uartInstance, int baudRate)
{
    uart_init(uartInstance, baudRate);

    gpio_set_function(DEF_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(DEF_RX_PIN, GPIO_FUNC_UART);
}

void picoBoard::sendData(const uint8_t* data, size_t length)
{
    uart_write_blocking(picoBoard::uart0, data, length);
}