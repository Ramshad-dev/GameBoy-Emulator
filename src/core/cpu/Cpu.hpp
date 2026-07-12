#include "cpuState.hpp"
#include "bus/Bus.hpp"

class Cpu{
    public:
        Cpu();
        void reset();
        void setBus(Bus* bus){
            this->bus=bus;
        }
    private:
        cpuState State;
        Bus* bus = nullptr;
};