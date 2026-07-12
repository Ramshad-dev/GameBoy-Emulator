#include "Ppu.hpp"

uint8_t PPU::readVRAM(uint16_t addr)
{
    return vram[addr];
}

void PPU::writeVRAM(uint16_t addr, uint8_t value)
{
    vram[addr] = value;
}

void PPU::tick()
{
}