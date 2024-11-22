#pragma once
#include "dataHandler.h"
#include "ILX511.h"
#include <vector>
#include <cstdint>

dataHandler::dataHandler() {}

std::vector<uint16_t> dataHandler::compressRLE(const std::vector<uint16_t>& data)
{
    std::vector<uint16_t> compressedData;
    SONYILX511::MAX_INTENSITY_VALUE;
    uint16_t count;
    uint16_t value;
    uint16_t previousValue;
    // NOTE: All these uint16 are technically only 12 bits due to having
    // a 12 bit ADC.
    for (const uint16_t& intensity : data)
    {
        if (intensity < SONYILX511::MAX_INTENSITY_VALUE * ZERO_DEADZONE)
        {
            value = 0;
        } else
        {
            value = intensity;
        }
        count+= 1;
    };

    return compressedData;
}