#include "Processor.h"

//PCB Default Constructor
PCB::PCB(){
    state_ = State::NEW;
    exitStatus_ = -1;
}


//Process Constructors
Process::Process(){

}
Process::Process(unsigned long long size, int priority, int PID){
    control_.PID_ = PID;
    control_.priority_ = priority;
    size_ = size;
}

//scheduling priority comparison function
bool priorityCompare::operator()(const Process& a, const Process& b)
{
        return a.control_.priority_ < b.control_.priority_;
}

//Processor Default Constructor
Processor::Processor(){

}

//MEMBER FUNCTION IMPLEMENTATIONS
Process Processor::getCurrentProcess(){
    return currentProcess;
}

std::vector<int> Processor::fetchReadyQueue(){
    std::priority_queue<Process, std::vector<Process>, priorityCompare> reQueue;
    std::vector<int> final;
    while (!readyQueue.empty()){
        final.push_back(readyQueue.top().control_.PID_);
        reQueue.push(readyQueue.top());
        readyQueue.pop();
    }
    readyQueue = reQueue;
    return final;
}

bool Processor::addProcess(const Process& process){
    readyQueue.push(process);
    //not sure in what case would return false
    return true;
}