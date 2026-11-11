#pragma once
#include "cpuState.hpp"
#include "Bus.hpp"
#include <cstdint>



class Cpu{
    public:
        Cpu(Bus* bus);
        void reset();

        uint32_t step();
    private:
        cpuState State;
        Bus* bus = nullptr;

        void opNop();
        void opLdBCd16();
        void opLdBCa();
        void opInc_BC();
        void opInc_B();
        void opDec_B();

        using Handler = void (Cpu::*)();
        struct Instruction {
            Handler handler;
            uint8_t size;
            uint8_t cycles;
        };
        Instruction OpcodeTable[256];
        Instruction ExtendedOpcodeTable[256];             // 0xCB XX

        
        uint8_t fetch8();
        uint16_t fetch16();
        
        void execute();

};