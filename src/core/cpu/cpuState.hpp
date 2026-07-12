#include <cstdint>

typedef union {
    struct {
        uint8_t High;
        uint8_t Low;
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