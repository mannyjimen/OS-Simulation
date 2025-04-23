//Manuel Jimenez
#include "SimOS.h"

//SimOS constructor
SimOS::SimOS(int numberOfDisks, unsigned long long amountOfRAM,
    unsigned long long sizeOfOS){

}
//SimOS Member Functions
bool SimOS::NewProcess(unsigned long long size, int priority){
    int newPID = process_.getNextPID();
    PCB temp(size, priority, newPID);
    return process_.addProcess(newPID, temp);
}

bool SimOS::SimFork(){
    PCB fork = process_.getPCB(process_.getCurrentProcess());
    //when forking these are the only two pieces of data we care about (I THINK)
    return NewProcess(fork.size_, fork.priority_);
}

int SimOS::GetCPU(){
    return process_.getCurrentProcess();
}

std::vector<int> SimOS::GetReadyQueue(){
    return process_.fetchReadyQueue();
}