#pragma once

#include <cstdint>

class HRAM
{
public:
    uint8_t read(uint16_t addr);
    void write(uint16_t addr, uint8_t value);

private:
    uint8_t memory[0x7F] = {};
};