#include "../include/picoBoard.h"
#include <stdio.h>
#include <vector>

#define HIGH 1
#define LOW  0

const uint8_t picoBoard::UART_HEADER[] = {0x5A,0x45,0x4B,0x45};
const uint8_t picoBoard::UART_FOOTER[] = {0x4A,0x45,0x53,0x53};

picoBoard::picoBoard(){}


void picoBoard::init()
{
    uart_instance = uart0;
    initPins();
}

void picoBoard::initPins()
{
    uart_init(uart_instance, DEF_BAUD_RATE);

    gpio_set_function(DEF_TX_PIN, GPIO_FUNC_UART);
    gpio_set_function(DEF_RX_PIN, GPIO_FUNC_UART);

    adc_init();
    adc_gpio_init(ILX511_VOUT_PIN);
    adc_select_input(0); // Pin 26 in ADC0 per documentation

    gpio_init(ILX511_ROG_PIN);
    gpio_set_dir(ILX511_ROG_PIN, GPIO_OUT);
}

void picoBoard::startIntegrationTime(uint32_t integration_time)
{
    printf("Setting integration time\n");
    gpio_put(ILX511_ROG_PIN, 1);
    sleep_us(10);
    gpio_put(ILX511_ROG_PIN, 0);
    sleep_ms(integration_time); // I just noticed my naming scheme is all over the place lol. Pascal, Cammel, Snake, etc
    printf("Integration time set\n");
}

uint16_t picoBoard::readILX511()
{
    // Returns a value 0 -> 4095 based on incoming 0 - 3.3 volts
    return adc_read();
}

// void picoBoard::sendData(std::vector<uint16_t> data)
// {
//     const uint8_t* dataToSend = reinterpret_cast<const uint8_t*>(data.data());
//     size_t dataSize = data.size() * sizeof(uint16_t);
//     uart_write_blocking(uart_instance, UART_HEADER, PROTOCOL_SIZE);
//     uart_write_blocking(uart_instance, dataToSend, dataSize);
//     uart_write_blocking(uart_instance, UART_FOOTER, PROTOCOL_SIZE);
// }


void picoBoard::sendData(const std::vector<uint16_t>& data)
{
    printf("HEADER:");
    for (uint16_t val : data) {
        printf("%u,", val);
    }
    printf("FOOTER\n");
}


int picoBoard::getILX511ClockPin()
{
    return ILX511_CLOCK_PIN;
}