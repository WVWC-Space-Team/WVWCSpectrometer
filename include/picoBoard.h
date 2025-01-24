#pragma once
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include <cstdint>

class picoBoard
{
public:
    picoBoard();
    void init();

    // UART Functions
    void initUART(uart_inst_t* uartInstance, int baudRate);
    void sendData(const uint8_t* data, size_t length); // Uses bytes of data
private:
    // const int X_PIN = 0; // Use this for assigning pin names (maybe)
    static const int DEF_TX_PIN = 0;
    static const int DEF_RX_PIN = 1;
    static const int DEF_BAUD_RATE = 115200;
    uart_inst_t* uart0;
    static const uint8_t UART_HEADER[];
    static const uint8_t UART_FOOTER[];
};
