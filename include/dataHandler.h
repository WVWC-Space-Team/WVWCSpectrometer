#pragma once
#include <cstdint>
#include <vector>

class dataHandler
{
public:
    dataHandler();

    std::vector<uint16_t> compressRLE(const std::vector<uint16_t>& data);

private:
    double ZERO_DEADZONE = 0.1 // The deadzone percentage for when values will be zero
};