//Manuel Jimenez
#include "SimOS.h"

//SimOS constructor
SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM,
    unsigned long long sizeOfOS){

    memory_.setSizeRAM(amountOfRAM);
    NewProcess(sizeOfOS, 0);
    process_.setSizeOS(sizeOfOS);
}
//SimOS Member Functions
bool SimOS::NewProcess(unsigned long long size, int priority){
    unsigned long long newStartAddress = memory_.insertProcessMemory(size, process_.seeNextPID());
    if (newStartAddress == memory_.getMemorySize()){
        std::cout << "No space for process in memory." << std::endl;
        return false;
    }
    int newPID = process_.getNextPID();
    PCB temp(newPID, priority, size);
    allMemItems_.push_back({newStartAddress, size, newPID}); // new memory item

    return process_.addProcess(newPID, temp);
}

bool SimOS::SimFork(){
    PCB fork = process_.getPCB(process_.getCurrentProcess()); 
    unsigned long long newStartAddress = memory_.insertProcessMemory(fork.size_, process_.seeNextPID());
    if (newStartAddress == memory_.getMemorySize()){
        std::cout << "No space for process in memory." << std::endl;
        return false;
    }
    int newPID = process_.getNextPID();
    process_.addProcess(newPID, fork);
    process_.addChild(process_.getCurrentProcess(), newPID);

    allMemItems_.push_back({newStartAddress, fork.size_, newPID}); //inserting forked mem item

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

MemoryUse SimOS::GetMemory(){
    MemoryUse final;
    std::vector<processItem> temp = memory_.fetchMemoryLayout();
    for(processItem currItem: temp){
        final.push_back({currItem.startAddress_, currItem.endAddress_ - currItem.startAddress_, currItem.PID_});
    }
    return final;
}

void SimOS::printReadyQueue(){
    std::vector<int> currReadyQueue = GetReadyQueue();
    for (int PID: currReadyQueue)
        std::cout << PID << " - ";
    std::cout << std::endl;
}

void SimOS::printMemoryLayout(){
    std::cout << "All Current Memory Items:\n";
    MemoryUse currMemoryLayout = GetMemory();
    for(MemoryItem currItem: currMemoryLayout){
        std::cout << currItem.itemAddress << " --- " << currItem.itemAddress + currItem.itemSize << " | PID: " << currItem.PID;
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

void SimOS::printMemoryHoles(){
    std::cout << "All Current Memory Holes:\n";
    std::vector<std::pair<unsigned long long, unsigned long long>> currMemHoles = memory_.fetchMemoryHoles();
    for(std::pair<unsigned long long, unsigned long long> currentHole: currMemHoles)
        std::cout << currentHole.first << " --- " << currentHole.second << std::endl;
}