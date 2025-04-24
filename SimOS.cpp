//Manuel Jimenez
#include "SimOS.h"

//SimOS constructor
SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM,
    unsigned long long sizeOfOS){
    process_.setSizeOS(sizeOfOS);
}
//SimOS Member Functions
bool SimOS::NewProcess(unsigned long long size, int priority){
    int newPID = process_.getNextPID();
    PCB temp(size, priority, newPID);
    return process_.addProcess(newPID, temp);
}

bool SimOS::SimFork(){
    PCB fork = process_.getPCB(process_.getCurrentProcess());
    int newPID = process_.getNextPID();
    process_.addChild(process_.getCurrentProcess(), newPID);
    return process_.addProcess(newPID, fork);
}

void SimOS::SimExit(){
    process_.exitProcess();
}

int SimOS::GetCPU(){
    return process_.getCurrentProcess();
}

std::vector<int> SimOS::GetReadyQueue(){
    return process_.fetchReadyQueue();
}

void SimOS::printReadyQueue(){
    std::vector<int> currReadyQueue = GetReadyQueue();
    for (int PID: currReadyQueue)
        std::cout << PID << " - ";
    std::cout << std::endl;
}