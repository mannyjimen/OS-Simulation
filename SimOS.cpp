//Manuel Jimenez
#include "SimOS.h"

//SimOS constructor
SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM,
    unsigned long long sizeOfOS){

}

//SimOS Member Functions
bool SimOS::NewProcess(unsigned long long size, int priority){
    Process temp(size, priority, ++PIDCounter);
    return processor_.addProcess(temp);
}

bool SimOS::SimFork(){
    Process fork = processor_.getCurrentProcess();
    return NewProcess(fork.size_, fork.control_.priority_);
}

int SimOS::GetCPU(){
    return processor_.getCurrentProcess().control_.PID_;
}

std::vector<int> SimOS::GetReadyQueue(){
    return processor_.fetchReadyQueue();
}