#pragma once
#include "dataHandler.h"
#include "ILX511.h"
#include <vector>
#include <cstdint>

dataHandler::dataHandler(){}

std::vector<uint16_t>* dataHandler::compressRLE(const std::vector<uint16_t>& data)
{
    std::vector<uint16_t>* compressedData = new std::vector<uint16_t>();
    SONYILX511::MAX_INTENSITY_VALUE;
    uint16_t count = 0;
    uint16_t value;
    uint16_t previousValue = 0;
    // NOTE: All these uint16 are technically only 12 bits due to having
    // a 12 bit ADC built into the XIAO RP2040.
    for (const uint16_t& intensity : data)
    {
        if (intensity < SONYILX511::MAX_INTENSITY_VALUE * ZERO_DEADZONE)
        {
            value = 0;
        } else
        {
            value = intensity;
        }
        if (value > previousValue - COMPARE_DEADZONE && value < previousValue + COMPARE_DEADZONE)
        {
            count+= 1;
        } else
        {
            if (count) // Takes care of instance where first value is 0
            {
                compressedData->push_back(value);
                compressedData->push_back(count);
                count = 0;
            }
        }
    };

    return compressedData;
}

bool dataHandler::checksumAmountOfSamples(std::vector<uint16_t>* compressedData)
{
    // Every second element is the count of times that value appears. The value should equal 2048.
    // TODO: for every second element add value to count, if count 2048 return true else false
}

void dataHandler::updateZeroDeadzone(double newDeadzone)
{
    ZERO_DEADZONE = newDeadzone;
};

void dataHandler::updateCompareDeadzone(int newDeadzone)
{
    // NOTE: The compare deadzone is used to compare two values during the RLE compression algorithm.
    // If the current value is within the range of "COMPARE_DEADZONE" away, the value is counted as the same.
    // For example, if the current value is 600 and the previous was 590 and the deadzone is set to 30, the
    // current value will be counted as the same ass the last one.
    // TODO: Needs testing. Kind of seems like it might be easier to just reduce quality.
    COMPARE_DEADZONE = newDeadzone;
};