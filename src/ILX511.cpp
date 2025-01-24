#pragma once
#include "ILX511.h"
#include <vector>

SONYILX511::SONYILX511(picoBoard& _board): board(_board), integrationTime(10), clockSpeed(100000) {}

std::vector<uint16_t> SONYILX511::collectData()
{
    std::vector<uint16_t> pixelData(PIXEL_COUNT);

    board.startIntegrationTime(integrationTime);
    int clockPin = board.getILX511ClockPin();

    int sleepTime = 1000000 / clockSpeed; // In useconds 

    for (int i = 0; i < DUMMY_PIXELS_START; i++)
    { // Skips the first dummy pixels
        gpio_put(clockPin, 1);
        sleep_us(sleepTime/2);
        gpio_put(clockPin, 0);
        sleep_us(sleepTime/2);
    }

    for (int i = 0; i < PIXEL_COUNT; i++)
    {
        gpio_put(clockPin, 1);
        sleep_us(sleepTime/2);
        pixelData[i] = board.readILX511();
        gpio_put(clockPin, 0);
        sleep_us(sleepTime/2);
    }

    for (int i = 0; i < DUMMY_PIXELS_END; i++)
    { // Skips the end dummy pixels
        gpio_put(clockPin, 1);
        sleep_us(sleepTime/2);
        gpio_put(clockPin, 0);
        sleep_us(sleepTime/2);
    }
    // TODO: Pin state is low at the end. Check if this is okay.

    return pixelData;
}

bool SONYILX511::setClockSpeed(int speed_hz)
{
    if (speed_hz <= 2000000 && speed_hz >= 100)
    {
        clockSpeed = speed_hz;
        return true;
    } else
    {
        return false;
    };
};

bool SONYILX511::setIntegrationTime(uint32_t time_ms)
{
    // TODO: Figure out a good max integration time
    if ((time_ms % 10 == 0) && (time_ms > 9)) // add && (time_ms < x) : (find x)
    {
        integrationTime = time_ms;
        return true;
    } else
    {
        return false;
    };
};