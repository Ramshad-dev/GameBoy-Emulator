#pragma once
#include <cstdint>

typedef union {
    struct {
        uint8_t high;
        uint8_t low;
    };
    uint16_t Word;
} reg16;

struct cpuState{
    reg16 AF,BC,DE,HL;
    uint16_t SP;
    uint16_t PC;
};

/*
in reg AF Low byte is flag znhc0000
z=zero 
n=subtraction(BCD)
h=halfcarry(BCD)
c=carry
*/

static constexpr uint8_t FLAG_Z = 0x80;
static constexpr uint8_t FLAG_N = 0x40;
static constexpr uint8_t FLAG_H = 0x20;
static constexpr uint8_t FLAG_C = 0x10;

// Set a flag
void setFlag(cpuState state,uint8_t flag) {
    state.AF.low |= flag;
}

// Clear a flag
void clearFlag(cpuState state,uint8_t flag) {
    state.AF.low &= ~flag;
}

// Read a flag
bool getFlag(cpuState state,uint8_t flag){
    return (state.AF.low & flag) != 0;
}

// Update a flag
void updateFlag(cpuState state,uint8_t flag, bool value) {
    if (value)
        setFlag(state,flag);
    else
        clearFlag(state,flag);
}
