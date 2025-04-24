#ifndef _PROCESSOR_
#define _PROCESSOR_

#include <vector>
#include <queue>
#include <unordered_map>

enum class State{
    NEW,
    READY,
    RUNNING,
    WAITING,
    TERMINATED,
};

struct PCB{
    int PID_;
    int priority_;
    //children specified by PID
    std::vector<int> children_ = std::vector<int>();
    int exitStatus_ = -1;
    unsigned long long processAddress_;
    unsigned long long size_;
    State state_;

    PCB();
    PCB(int PID, int priority, unsigned long long size);
};

/// custom function object to compare process priority (for readyQueue)
//COMPARING PRIO of two PIDS 

class ProcessManagement{
    public:
    //compare function for readyQueue
    struct priorityCompare
    {
        bool operator()(const std::pair<int,int>& lhs, const std::pair<int,int>& rhs);
    };
    //default constructor
    ProcessManagement();
    void setSizeOS(unsigned long long sizeOfOS);
    void refreshCurrent();
    //for SimOS getCPU
    int getCurrentProcess();
    //for SimOS GetReadyQueue
    std::vector<int> fetchReadyQueue();
    //adding process to readyQueue
    int getNextPID();
    PCB getPCB(int PID);
    void addChild(int parent, int child);

    bool addProcess(int newPID, PCB newPCB);
    void exitProcess();


    private:

    int currentProcess;
    int PIDCounter = 0;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, priorityCompare> readyQueue;
    std::unordered_map<int, PCB> processMap;
};

#endif //_PROCESSOR_