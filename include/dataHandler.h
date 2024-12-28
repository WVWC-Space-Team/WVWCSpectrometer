#pragma once
#include <cstdint>
#include <vector>

class dataHandler
{
public:
    dataHandler();

    std::vector<uint16_t>* compressRLE(const std::vector<uint16_t>& data);
    bool checksumAmountOfSamples(std::vector<uint16_t>* compressedData);
    void updateZeroDeadzone(double newDeadzone);
    void updateCompareDeadzone(int newDeadzone);

private:
    double ZERO_DEADZONE = 0.1; // The deadzone percentage for when values will be zero
    int COMPARE_DEADZONE = 15;  // The deadzone between previous values for it to be counted as the same
};