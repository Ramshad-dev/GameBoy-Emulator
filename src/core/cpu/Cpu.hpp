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
        bool stopped;
        bool halted;

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
        void opStop();
        void opLd_DE_d16();
        void opLd_aDE_A();
        void opInc_DE();
        void opInc_D();
        void opDec_D();
        void opLd_D_d8();
        void opRla();
        void opJr_e8();
        void opAdd_HL_DE();
        void opLd_A_aDE();
        void opDec_DE();
        void opInc_E();
        void opDec_E();
        void opLd_E_d8();
        void opRra();
};