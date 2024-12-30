#include "ILX511.h"

SONYILX511::SONYILX511(picoBoard& board): boardClass(board), integrationTime(10), clockSpeed(100000) {}

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

bool SONYILX511::setIntegrationTime(int time_ms)
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