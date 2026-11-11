#include "Cpu.hpp"

Cpu::Cpu(Bus* bus){
    
    // Set bus to cpu
    this->bus=bus;

    // Initialize opcode table
    OpcodeTable[0x00] = {&Cpu::opNop,     1,  4};
    OpcodeTable[0x01] = {&Cpu::opLdBCd16, 3, 12};
    OpcodeTable[0x02] = {&Cpu::opLdBCa,   1,  8};
    OpcodeTable[0x03] = {&Cpu::opInc_BC,  1,  8};
    OpcodeTable[0x04] = {&Cpu::opInc_B,   1,  4};
    OpcodeTable[0x05] = {&Cpu::opDec_B,   1,  4};
}

void Cpu::reset(){
    State.PC=0x100; 
    State.SP=0xFFFE;
}

uint8_t Cpu::fetch8(){
    return bus->read(State.PC++);   
}

uint16_t Cpu::fetch16(){
    uint8_t low = fetch8();
    uint8_t high = fetch8();
    return (uint16_t) high<<8 | low;
}


void Cpu::execute(){
    uint8_t opcode = fetch8();
    uint8_t cycle=this->OpcodeTable[opcode].cycles;
    uint8_t size=this->OpcodeTable[opcode].size;
    (this->*OpcodeTable[opcode].handler)();
}

void Cpu::opNop(){
    return;
}

void Cpu::opLdBCd16(){
    State.BC.Word=fetch16();
}