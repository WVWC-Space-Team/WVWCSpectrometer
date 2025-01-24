#pragma once
#include "pico/stdlib.h"
#include "hardware/adc.h"
#include "hardware/uart.h"
#include "hardware/pwm.h"
#include <cstdint>

class picoBoard
{
public:
    picoBoard();
    void init();

    // UART Functions
    void initPins(uart_inst_t* uartInstance, int baudRate);
    void sendData(std::vector<uint16_t> data);
    // ILX511 ADC Pin Reading
    uint16_t readILX511();
    void startIntegrationTime(uint32_t integrationTime);
    int getILX511ClockPin();

private:
    // const int X_PIN = 0; // Use this for assigning pin names (maybe)
    static const int DEF_TX_PIN = 0;
    static const int DEF_RX_PIN = 1;
    static const int ILX511_VOUT_PIN = 26; // ADC pin
    static const int ILX511_CLOCK_PIN = 27; // TODO: CHECK!!
    static const int ILX511_ROG_PIN = 28; // TODO: CHECK!!
    static const int DEF_BAUD_RATE = 115200;
    static const size_t PROTOCOL_SIZE = 2;
    uart_inst_t* uart0;
    static const uint8_t UART_HEADER[];
    static const uint8_t UART_FOOTER[];
};
