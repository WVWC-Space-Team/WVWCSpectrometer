#pragma once
#include "picoBoard.h"

const uint8_t picoBoard::UART_HEADER[] = {0xAA, 0xAA}; // TODO: Decide on a header and footer
const uint8_t picoBoard::UART_FOOTER[] = {0xBB, 0xBB};

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
    uart_write_blocking(picoBoard::uart0, picoBoard::UART_HEADER, picoBoard::PROTOCOL_SIZE);
    uart_write_blocking(picoBoard::uart0, data, length);
    uart_write_blocking(picoBoard::uart0, picoBoard::UART_FOOTER, picoBoard::PROTOCOL_SIZE);
}