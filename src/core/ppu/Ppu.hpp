#pragma once

#include <cstdint>

class PPU
{
public:
    void tick();

    uint8_t readVRAM(uint16_t addr);
    void writeVRAM(uint16_t addr, uint8_t value);

    uint8_t readOAM(uint16_t addr);
    void writeOAM(uint16_t addr, uint8_t value);

private:
    uint8_t vram[0x2000] = {};
    uint8_t oam[0xA0] = {};
};