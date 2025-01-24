#pragma once
#include "picoBoard.h"

const uint8_t picoBoard::UART_HEADER[] = {0xAA, 0xAA}; // TODO: Decide on a header and footer
const uint8_t picoBoard::UART_FOOTER[] = {0xBB, 0xBB};

picoBoard::picoBoard(){}


void picoBoard::init()
{
    initPins(picoBoard::uart0, 115200);
}

void picoBoard::initPins(uart_inst_t* uartInstance, int baudRate)
{
    uart_init(uartInstance, baudRate);

    gpio_set_function(DEF_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(DEF_RX_PIN, GPIO_FUNC_UART);

    adc_gpio_init(picoBoard::ILX511_OUTPUT_PIN);
    adc_select_input(0); // Pin 26 in ADC0 per documentation
}

uint16_t picoBoard::readILX511()
{
    // Returns a value 0 -> 4095 based on incoming 0 - 3.3 volts
    return adc_read();
}

void picoBoard::sendData(const uint8_t* data, size_t length)
{
    uart_write_blocking(picoBoard::uart0, picoBoard::UART_HEADER, picoBoard::PROTOCOL_SIZE);
    uart_write_blocking(picoBoard::uart0, data, length);
    uart_write_blocking(picoBoard::uart0, picoBoard::UART_FOOTER, picoBoard::PROTOCOL_SIZE);
}