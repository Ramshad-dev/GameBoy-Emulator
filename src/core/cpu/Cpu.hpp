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
        void opLd_BC_d16();
        void opLd_aBC_A();
        void opInc_BC();
        void opInc_B();
        void opDec_B();
        void opLd_B_d8();
        void opRlca();
        void opLd_a16_SP();
        void opAdd_HL_BC();
        void opLd_A_aBC();
        void opDec_BC();
        void opInc_C();
        void opDec_C();
        void opLd_C_d8();
        void opRrca();

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