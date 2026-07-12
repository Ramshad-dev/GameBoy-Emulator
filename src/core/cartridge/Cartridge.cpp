#include <iostream>
#include <fstream>

#include "Cartridge.hpp"

bool Cartridge::loadROM(const char* filename){
    std::ifstream cartridge(filename,std::ios::binary);
    if(!cartridge){
        std::cerr <<"failed to open ROM\n ";
        return false;
    }
    cartridge.seekg(0,std::ios::end);
    std::streamsize romSize = cartridge.tellg(); //determine size of rom
    cartridge.seekg(0,std::ios::beg);

    ROM.resize(romSize); 

    //Read ROM data into memory
    cartridge.read(
        reinterpret_cast<char*>(ROM.data()),
        romSize
    );
    std::cout << "ROM Size: " << ROM.size() << " bytes\n";
    return true;
}

uint8_t Cartridge::read(uint16_t addr){
    return ROM[addr];
}

void Cartridge::write(uint16_t addr, uint8_t byte){
    ROM[addr]=byte;
}