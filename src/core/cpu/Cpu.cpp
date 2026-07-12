#include "Cpu.hpp"

void Cpu::reset(){
    State.PC=0x100; 
    State.SP=0xFFFE;
}
