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

    adc_gpio_init(picoBoard::ILX511_VOUT_PIN);
    adc_select_input(0); // Pin 26 in ADC0 per documentation

    gpio_init(ILX511_ROG_PIN);
    gpio_set_dir(ILX511_ROG_PIN, GPIO_OUT);
}

void picoBoard::startIntegrationTime(uint32_t integration_time)
{
    gpio_put(ILX511_ROG_PIN, 1);
    sleep_us(10);
    gpio_put(ILX511_ROG_PIN, 0);
    sleep_ms(integration_time); // I just noticed my naming scheme is all over the place lol. Pascal, Cammel, Snake, etc
}

uint16_t picoBoard::readILX511()
{
    // Returns a value 0 -> 4095 based on incoming 0 - 3.3 volts
    return adc_read();
}

void picoBoard::sendData(std::vector<uint16_t> data)
{
    const uint8_t* dataToSend = reinterpret_cast<const uint8_t*>(data.data());
    size_t dataSize = data.size() * sizeof(uint16_t);
    uart_write_blocking(picoBoard::uart0, picoBoard::UART_HEADER, picoBoard::PROTOCOL_SIZE);
    uart_write_blocking(picoBoard::uart0, dataToSend, dataSize);
    uart_write_blocking(picoBoard::uart0, picoBoard::UART_FOOTER, picoBoard::PROTOCOL_SIZE);
}

int picoBoard::getILX511ClockPin()
{
    return ILX511_CLOCK_PIN;
}