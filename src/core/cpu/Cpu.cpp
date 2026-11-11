#include "Cpu.hpp"

Cpu::Cpu(Bus* bus){
    
    // Set bus to cpu
    this->bus=bus;

    // Initialize opcode table
    OpcodeTable[0x00] = {&Cpu::opNop,       1,  4};
    OpcodeTable[0x01] = {&Cpu::opLd_BC_d16, 3, 12};
    OpcodeTable[0x02] = {&Cpu::opLd_aBC_A,  1,  8};
    OpcodeTable[0x03] = {&Cpu::opInc_BC,    1,  8};
    OpcodeTable[0x04] = {&Cpu::opInc_B,     1,  4};
    OpcodeTable[0x05] = {&Cpu::opDec_B,     1,  4};
    OpcodeTable[0x06] = {&Cpu::opLd_B_d8,   2,  8};
    OpcodeTable[0x07] = {&Cpu::opRlca,      1,  4};
    OpcodeTable[0x08] = {&Cpu::opLd_a16_SP, 3, 20};
    OpcodeTable[0x09] = {&Cpu::opAdd_HL_BC, 1,  8};
    OpcodeTable[0x0A] = {&Cpu::opLd_A_aBC,  1,  8};
    OpcodeTable[0x0B] = {&Cpu::opDec_BC,    1,  8};
    OpcodeTable[0x0C] = {&Cpu::opInc_C,     1,  4};
    OpcodeTable[0x0D] = {&Cpu::opDec_C,     1,  4};
    OpcodeTable[0x0E] = {&Cpu::opLd_C_d8,   2,  4};
    OpcodeTable[0x0F] = {&Cpu::opRrca,      1,  4};
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

void Cpu::opLd_BC_d16(){
    State.BC.Word=fetch16();
}

void Cpu::opLd_aBC_A(){
    bus->write(State.BC.Word,State.AF.high);
}

void Cpu::opInc_BC(){
    State.BC.Word++;
}

void Cpu::opInc_B(){
    if((State.BC.high & 0x0F)==0x0F)setFlag(State,FLAG_H);
    else clearFlag(State,FLAG_H);
    State.BC.high++;
    if(State.BC.high==0x00) setFlag(State,FLAG_Z);
    else clearFlag(State,FLAG_Z);
    clearFlag(State,FLAG_N);
}

void Cpu::opDec_B(){
    if((State.BC.high & 0x0F)==0x00) setFlag(State,FLAG_H);
    else clearFlag(State,FLAG_H);
    State.BC.high--;
    if(State.BC.high==0x00) setFlag(State,FLAG_Z);
    else clearFlag(State,FLAG_Z);
    setFlag(State,FLAG_N);
}

void Cpu::opLd_B_d8(){
    State.BC.high=fetch8();
}

void Cpu::opRlca(){
    bool carry = (State.AF.high & 0x80)>>7;
    State.AF.high = (State.AF.high<<1) | carry;
    clearFlag(State,FLAG_Z);
    clearFlag(State,FLAG_N);
    clearFlag(State,FLAG_H);
    updateFlag(State,FLAG_C,carry);
}

void Cpu::opLd_a16_SP(){
    uint16_t addr = fetch16();
    bus->write(addr,State.SP & 0x00FF);
    bus->write(addr + 1,(State.SP & 0xFF00)>>8);
}

void Cpu::opAdd_HL_BC(){
    uint32_t res = State.HL.Word + State.BC.Word;
    clearFlag(State,FLAG_N);
    if((State.HL.Word & 0x0FFF)+(State.BC.Word & 0x0FFF)>0x0FFF) setFlag(State,FLAG_H);
    else clearFlag(State,FLAG_H);
    if(res>0xFFFF) setFlag(State,FLAG_C);
    else clearFlag(State,FLAG_C);
    State.HL.Word = res & 0xFFFF;
}

void Cpu::opLd_A_aBC(){
    State.AF.high=bus->read(State.AF.Word);
}

void Cpu::opDec_BC(){
    State.BC.Word--;
}

void Cpu::opInc_C(){
    if((State.BC.low & 0x0F)==0x0F)setFlag(State,FLAG_H);
    else clearFlag(State,FLAG_H);
    State.BC.low++;
    if(State.BC.low==0x00) setFlag(State,FLAG_Z);
    else clearFlag(State,FLAG_Z);
    clearFlag(State,FLAG_N);
}

void Cpu::opDec_C(){
    if((State.BC.low & 0x0F)==0x00) setFlag(State,FLAG_H);
    else clearFlag(State,FLAG_H);
    State.BC.low--;
    if(State.BC.low==0x00) setFlag(State,FLAG_Z);
    else clearFlag(State,FLAG_Z);
    setFlag(State,FLAG_N);
}

void Cpu::opLd_C_d8(){
    State.BC.low=fetch8();
}

void Cpu::opRrca(){
    bool carry = State.AF.high & 0x01;
    State.AF.high = (carry<<7) |(State.AF.high>>1) ;
    clearFlag(State,FLAG_Z);
    clearFlag(State,FLAG_N);
    clearFlag(State,FLAG_H);
    updateFlag(State,FLAG_C,carry);
}