#include "HRam.hpp"

uint8_t HRAM::read(uint16_t addr)
{
    return memory[addr];
}

void HRAM::write(uint16_t addr, uint8_t value)
{
    memory[addr] = value;
}