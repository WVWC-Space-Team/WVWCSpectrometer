#pragma once

class SONYILX511
{
public:
    // Constructor
    SONYILX511();

    // Set the integration time in term of ms; Must be a multiple of 10
    bool setIntegrationTime(int time_ms);

    // Set the clock speed in hertz; Max 2MHz, Min 100Hz
    bool setClockSpeed(int speed_hz);


private:
    static const int MAX_CLOCK_SPEED = 2000000; // Maximum clock speed as per documentation; 2MHz
    static const int REQUIRED_CYCLES = 2088;    // Constant cycles to obtain all data as per ILX511 documentation
    int integrationTime;                        // Integration time in ms; must be a mulitple of 10
    int clockSpeed;                             // Clock speed in Hz; max 2MHz, min 100Hz
};