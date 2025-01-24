#pragma once
#include <cstdint>
#include "picoBoard.h"

class SONYILX511
{
public:
    // Constructor
    SONYILX511(picoBoard& _board);
    static const int MAX_INTENSITY_VALUE = 4095;

    // Set the integration time in term of ms; Must be a multiple of 10
    bool setIntegrationTime(uint32_t time_ms);

    // Set the clock speed in hertz; Max 2MHz, Min 100Hz
    bool setClockSpeed(int speed_hz);

    // Collect data
    std::vector<uint16_t> collectData();

private:
    static const int MAX_CLOCK_SPEED    = 2000000; // Maximum clock speed as per documentation; 2MHz
    static const int REQUIRED_CYCLES    = 2088;    // Constant cycles to obtain all data as per ILX511 documentation (Can be 2087, CHECK)
    static const int PIXEL_COUNT        = 2048;    // Amount of optical pixels there are
    static const int DUMMY_PIXELS_START = 32;      // Amount of starting dummy pixels
    static const int DUMMY_PIXELS_END   = 20;      // Amount of end dummy pixels. Added some for safety.
    int integrationTime;                           // Integration time in ms; must be a mulitple of 10
    int clockSpeed;                                // Clock speed in Hz; max 2MHz, min 100Hz
    picoBoard& board; // TODO: Idk if this is a good way to do this? Is it?
};