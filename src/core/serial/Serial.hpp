#pragma once

#include <cstdint>

class Serial
{
public:
    void tick();

    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);
};