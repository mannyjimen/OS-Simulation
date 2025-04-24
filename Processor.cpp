#include "Processor.h"

//PCB Default Constructor
PCB::PCB(){
    state_ = State::NEW;
    exitStatus_ = -1;
}

PCB::PCB(int PID, int priority, unsigned long long size){
    PID_ = PID;
    priority_ = priority;
    size_ = size;
}

ProcessManagement::ProcessManagement(){
    PCB temp(getNextPID(), 0, -1);
    addProcess(temp.PID_, temp);
    refreshCurrent();
}

void ProcessManagement::setSizeOS(unsigned long long sizeOfOS){
    processMap[1].size_ = sizeOfOS;
}

void ProcessManagement::refreshCurrent(){
    currentProcess = readyQueue.top().first;
}

//scheduling priority comparison function
bool ProcessManagement::priorityCompare::operator()(
    const std::pair<int,int>& lhs, 
    const std::pair<int,int>& rhs)
{
    return rhs.second > lhs.second;
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
    std::vector<int> finalreadyQueue(temp.size());
    int i = 0;
    while(!temp.empty()){
        finalreadyQueue[i] = temp.top().first;
        temp.pop();
        i++;
    }
    return finalreadyQueue;
}

int ProcessManagement::getNextPID(){
    return ++PIDCounter;
}

void ProcessManagement::addChild(int parent, int child){
    processMap[parent].children_.push_back(child);
}

bool ProcessManagement::addProcess(int newPID, PCB newPCB){
    processMap[newPID] = newPCB;
    readyQueue.push({newPID, newPCB.priority_});
    refreshCurrent();
    //not sure in what case would return false
    return true;
}

void ProcessManagement::exitProcess(){
    processMap[currentProcess].state_ = State::TERMINATED;
    readyQueue.pop();
    refreshCurrent();
}