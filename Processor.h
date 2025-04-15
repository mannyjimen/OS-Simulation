#ifndef _PROCESSOR_
#define _PROCESSOR_

#include <vector>
#include <queue>

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
    int exitStatus_;
    unsigned long long processAddress_;
    State state_;

    PCB();
};

struct Process{
    PCB control_;
    unsigned long long size_;

    Process();
    Process(unsigned long long size, int priority, int PID);
};

/// custom function object to compare process priority (for readyQueue)
struct priorityCompare
{
    bool operator()(const Process& a, const Process& b);
};

class Processor{
    public:
    //default constructor
    Processor();
    //for SimOS getCPU
    Process getCurrentProcess();
    //for SimOS GetReadyQueue
    std::vector<int> fetchReadyQueue();
    //adding process to readyQueue
    bool addProcess(const Process& process);

    private:
    Process currentProcess;
    std::priority_queue<Process, std::vector<Process>, priorityCompare> readyQueue;
};

#endif //_PROCESSOR_