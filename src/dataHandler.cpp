#pragma once
#include "dataHandler.h"
#include "ILX511.h"
#include <vector>
#include <cstdint>

dataHandler::dataHandler(){}

std::vector<uint16_t> dataHandler::compressRLE(const std::vector<uint16_t>& data)
{   
    if (data.empty()) { return {}; } // no data, so return

    std::vector<uint16_t> compressedData;
    compressedData.reserve(data.size());
    
    uint16_t count = 0;
    uint16_t previousValue = 0;
    uint16_t threshold = SONYILX511::MAX_INTENSITY_VALUE * ZERO_DEADZONE; // no need to recompute

    for (size_t i = 0; i < data.size(); i++)
    {
        uint16_t intensity = data[i];
        uint16_t value = (intensity < threshold) ? 0 : intensity;

        if (i == 0 || value < previousValue - COMPARE_DEADZONE || value > previousValue + COMPARE_DEADZONE)
        {
            if (count > 0)
            {
                compressedData.push_back(previousValue);
                compressedData.push_back(count);
            }
            previousValue = value;
            count = 1;
        } else
        {
            ++count;
        }
    }

    if (count > 0)
    {
        compressedData.push_back(previousValue);
        compressedData.push_back(count);
    }

    compressedData.shrink_to_fit(); // not necessary, but can reduce memory usage
    return (compressedData.size() >= data.size()) ? data : compressedData;
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