//Manuel Jimenez
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
    if(rhs.second == lhs.second)
        return rhs.first < lhs.first;
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

std::vector<int> ProcessManagement::getChildren(int PID){
    std::vector<int> children;
    for(int child: processMap[PID].children_)
        children.push_back(child);

    return children;
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

void ProcessManagement::reviveProcess(int PID){
    readyQueue.push({PID, processMap[PID].priority_});
}

void ProcessManagement::exitProcess(){
    processMap[currentProcess].state_ = State::TERMINATED;
    readyQueue.pop();
    if (checkForWaitingParent(currentProcess)){
        parentUnwait(processMap[currentProcess].parent_, currentProcess);
    }
    refreshCurrent();
}

bool ProcessManagement::checkForWaitingParent(int childPID){
    if (waitingParents.count(processMap[currentProcess].parent_)){
        return true;
    }
    return false;
}

bool ProcessManagement::waitParent(){
    //wait parent IF it has at least 1 child
    if (processMap[currentProcess].children_.size() == 0)
        return false;
    //in case parent has a terminated child it can use
    for(auto x: processMap[currentProcess].children_){
        if (processMap[x].state_ == State::TERMINATED){
            processMap[currentProcess].children_.erase(x);
            return false;
        }
    }
    processMap[currentProcess].state_ = State::WAITING;
    waitingParents.insert(currentProcess);
    readyQueue.pop();
    refreshCurrent();
    return true;
}

void ProcessManagement::parentUnwait(int parentPID, int childPID){
    reviveProcess(parentPID);
    processMap[parentPID].children_.erase(childPID);
    waitingParents.erase(parentPID);
}

bool ProcessManagement::waitProcess(){
    processMap[currentProcess].state_ == State::WAITING;
    readyQueue.pop();
    refreshCurrent();
    return true;
}

void ProcessManagement::unwaitProcess(int PID){
    if (PID <= 1) return;
    processMap[PID].state_ = State::READY;
    addProcess(PID, processMap[PID]);
}

//termination for cascading
void ProcessManagement::terminateProcess(int PID){
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, ProcessManagement::priorityCompare> newReadyQueue;
    while(!readyQueue.empty()){
        std::pair<int,int> currProcess = readyQueue.top();
        readyQueue.pop();
        if(currProcess.first != PID){
            newReadyQueue.push(currProcess);
        }
    }
    processMap[PID].state_ = State::TERMINATED;
    readyQueue = newReadyQueue;
}