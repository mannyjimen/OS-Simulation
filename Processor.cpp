#include "Processor.h"

//PCB Default Constructor
PCB::PCB(){
    state_ = State::NEW;
    exitStatus_ = -1;
}

PCB::PCB(int PID, int priority, unsigned long long size){
    
}

ProcessManagement::ProcessManagement(){
}

//scheduling priority comparison function
bool ProcessManagement::priorityCompare::operator()(
    const std::pair<int,int>& a, 
    const std::pair<int,int>& b)
{
    return a.second > b.second;
}

//MEMBER FUNCTION IMPLEMENTATIONS
int ProcessManagement::getCurrentProcess(){
    return currentProcess;
}

PCB ProcessManagement::getPCB(int PID){
    return processMap[PID];
}

std::vector<int> ProcessManagement::fetchReadyQueue(){
    auto temp = readyQueue;
    std::vector<int> finalreadyQueue;
    while (!temp.empty()){
        finalreadyQueue.push_back(temp.top().first);
        temp.pop();
    }
    return finalreadyQueue;
}

int ProcessManagement::getNextPID(){
    return ++PIDCounter;
}

bool ProcessManagement::addProcess(int newPID, PCB newPCB){
    processMap[newPID] = newPCB;
    readyQueue.push({newPID, newPCB.priority_});
    //not sure in what case would return false
    return true;
}