#pragma once
#include <cstdint>

class Joypad
{
public:
    uint8_t read();
    void write(uint8_t value);
};