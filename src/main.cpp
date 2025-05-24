#include <stdio.h>
#include <string>

#include "picoBoard.h"
#include "ILX511.h"
#include "dataHandler.h"

#include "hardware/uart.h"
#include "pico/stdlib.h"

int main()
{
    // Initialization
    stdio_init_all();

    sleep_ms(3000);

    picoBoard board;
    board.init();

    SONYILX511 sensor(board);
    sensor.setClockSpeed(1000000); // 1MHz for rn
    sensor.setIntegrationTime(100); // I still haven't quite decided how to use this

    dataHandler compressor;

    std::vector<uint16_t> data;
    std::vector<uint16_t> compressedData;

    while (true)
    {
        printf("Starting Data Collection\n");
        data = sensor.collectData();
        printf("Finished Data Collection\n");
        // compressedData = compressor.compressRLE(data);
        board.sendData(data);
        sleep_ms(5000);
    }
}