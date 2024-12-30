#pragma once
#include <cstdint>
#include "picoBoard.h"

class SONYILX511
{
public:
    // Constructor
    SONYILX511(picoBoard& board);
    static const int MAX_INTENSITY_VALUE = 4095;

    // Set the integration time in term of ms; Must be a multiple of 10
    bool setIntegrationTime(int time_ms);

    // Set the clock speed in hertz; Max 2MHz, Min 100Hz
    bool setClockSpeed(int speed_hz);


private:
    static const int MAX_CLOCK_SPEED = 2000000; // Maximum clock speed as per documentation; 2MHz
    static const int REQUIRED_CYCLES = 2088;    // Constant cycles to obtain all data as per ILX511 documentation (Can be 2087, CHECK)
    static const int PIXEL_COUNT     = 2048;    // Amount of optical pixels there are
    int integrationTime;                        // Integration time in ms; must be a mulitple of 10
    int clockSpeed;                             // Clock speed in Hz; max 2MHz, min 100Hz
    uint16_t DATA[PIXEL_COUNT];                 // Data collected from the spectrometer. (Will only be 12 bits)
    picoBoard& boardClass; // TODO: Idk if this is a good way to do this? Is it?
};