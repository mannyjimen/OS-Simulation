//Manuel Jimenez
#include "SimOS.h"

//SimOS constructor
SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM,
    unsigned long long sizeOfOS){
    
    memory_.setSizeRAM(amountOfRAM);
    allMemItems_.push_back({memory_.insertProcessMemory(sizeOfOS, 1), sizeOfOS, 1}); //OS memory item

    process_.setSizeOS(sizeOfOS);
}
//SimOS Member Functions
bool SimOS::NewProcess(unsigned long long size, int priority){
    int newPID = process_.getNextPID();
    PCB temp(newPID, priority, size);
    
    allMemItems_.push_back({memory_.insertProcessMemory(size, newPID), size, newPID}); // new memory item

    return process_.addProcess(newPID, temp);
}

bool SimOS::SimFork(){
    PCB fork = process_.getPCB(process_.getCurrentProcess()); 
    int newPID = process_.getNextPID();
    process_.addProcess(newPID, fork);
    process_.addChild(process_.getCurrentProcess(), newPID);

    allMemItems_.push_back({memory_.insertProcessMemory(fork.size_, newPID), fork.size_, newPID}); //inserting forked mem item

    return true;
}

void SimOS::SimExit(){
    if (process_.getCurrentProcess() == NO_PROCESS || process_.getCurrentProcess() == 1)
        return;
    memory_.removeProcessMemory(process_.getCurrentProcess());
    process_.exitProcess();
}

void SimOS::SimWait(){
    process_.waitParent();
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