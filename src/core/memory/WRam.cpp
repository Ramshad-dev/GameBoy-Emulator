#include "WRam.hpp"

uint8_t WRAM::read(uint16_t addr)
{
    return memory[addr];
}

void WRAM::write(uint16_t addr, uint8_t value)
{
    memory[addr] = value;
}