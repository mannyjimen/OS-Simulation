#ifndef _PROCESSOR_
#define _PROCESSOR_

#include "SimOS.h"

#include <vector>
#include <queue>

class Processor{
    public:
    Process getCurrentProcess();
    bool addProcess(Process);

    private:
    Process currentProcess;
    std::priority_queue<Process> readyQueue;
};

#endif //_PROCESSOR_