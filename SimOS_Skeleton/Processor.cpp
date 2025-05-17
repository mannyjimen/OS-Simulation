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

void ProcessManagement::setSizeOS(unsigned long long sizeOfOS){
    processMap[1].size_ = sizeOfOS;
}

void ProcessManagement::refreshCurrent(){
    currentProcess = readyQueue.top().first;
    //slow way of making sure every process has correct state
    processMap[currentProcess].state_ = State::RUNNING;
    std::vector<int> temp = fetchReadyQueue();
    for (int i = 1; i < temp.size(); i++)
        processMap[temp[i]].state_ = State::READY;
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

int ProcessManagement::seeNextPID(){
    return PIDCounter + 1;
}

void ProcessManagement::addChild(int parent, int child){
    processMap[parent].children_.insert(child);
    processMap[child].parent_ = parent;
    processMap[child].children_.clear();
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
    if (checkForWaitingParent(currentProcess)){
        parentUnwait(processMap[currentProcess].parent_, currentProcess);
    }
    readyQueue.pop();
    refreshCurrent();
}

bool ProcessManagement::checkForWaitingParent(int childPID){
    if (processMap[childPID].parent_ != -1 && processMap[processMap[childPID].parent_].state_ == State::WAITING){
        return true;
    }
    return false;
}

bool ProcessManagement::waitParent(){
    //wait parent IF it has at least 1 child
    if (processMap[currentProcess].children_.size() == 0)
        return false;
    processMap[currentProcess].state_ = State::WAITING;
    readyQueue.pop();
    refreshCurrent();
    return true;
}

void ProcessManagement::parentUnwait(int parentPID, int childPID){
    processMap[parentPID].state_ = State::READY;
    processMap[parentPID].children_.erase(childPID);
    addProcess(parentPID, processMap[parentPID]);
}