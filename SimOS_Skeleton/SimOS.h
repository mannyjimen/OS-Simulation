//Manuel Jimenez
#ifndef _SIM_OS_
#define _SIM_OS_

#include <iostream>
#include <string>
#include <vector>
#include <queue>

#include "Processor.h"
#include "Disk.h"
#include "MemoryManagement.h"

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
    SimOS(int numberOfDisks, unsigned long long amountOfRAM, unsigned long long sizeOfOS);
    bool NewProcess( unsigned long long size, int priority );
    bool SimFork();
    void SimExit();
    void SimWait();
    void DiskReadRequest( int diskNumber, std::string fileName );
    void DiskJobCompleted( int diskNumber );
    int GetCPU();
    std::vector<int> GetReadyQueue();
    MemoryUse GetMemory();
    FileReadRequest GetDisk( int diskNumber );
    std::queue<FileReadRequest> GetDiskQueue( int diskNumber );

    //helper functions
    // void printReadyQueue();
    // void printMemoryLayout();
    // void printMemoryHoles();
    // void printDisksAndJobs();


    private:
    ProcessManagement process_;
    Disks disk_;
    MemoryManagement memory_;
    MemoryUse allMemItems_;
};  

#endif //_SIM_OS_