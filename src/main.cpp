#pragma once
#include "./dataHandler.cpp"
#include "./ILX511.cpp"
#include "./picoBoard.cpp"

int main()
{
    // Initialization

    picoBoard board;
    board.init();

    SONYILX511 sensor(board);
    sensor.setClockSpeed(1000000); // 1MHz for rn
    sensor.setIntegrationTime(100); // I still haven't quite decided how to use this


    while (true)
    {
        // Capture data

        // Compress data

        // Send data over UART
    }
}