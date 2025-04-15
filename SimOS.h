//Manuel Jimenez

#ifndef _SIM_OS_
#define _SIM_OS_

#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

#include "Processor.h"
#include "RandomAccessMemory.h"
#include "Disk.h"

struct FileReadRequest
{
    int PID{0};
    std::string fileName{""};
};

struct MemoryItem
{
    unsigned long long itemAddress;
    unsigned long long itemSize;
    int PID; //PID of process using this chunk of memory
};

using MemoryUse = std::vector<MemoryItem>;

constexpr int NO_PROCESS{-1};

class SimOS{

    public:
    SimOS(int numberOfDisks, unsigned long long amountOfRAM,
    unsigned long long sizeOfOS);
    bool NewProcess(unsigned long long size, int priority);
    bool SimFork();
    void SimExit();
    void SimWait();
    void DiskReadRequest(int diskNumber, std::string fileName);
    void DiskJobCompleted(int diskNumber);
    int GetCPU();
    std::vector<int> GetReadyQueue();
    MemoryUse GetMemory();
    FileReadRequest GetDisk(int diskNumber);
    std::queue<FileReadRequest> GetDiskQueue(int diskNumber);

    private:
    Processor processor_;
    std::unordered_map<int, std::queue<Process>> disks_;
    RandomAccessMemory memory_;

    int PIDCounter;
    
};  

#endif //_SIM_OS_