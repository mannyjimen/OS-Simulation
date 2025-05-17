#ifndef _RAM_
#define _RAM_

#include <vector>
#include <iterator>

struct processItem{
    int PID_;
    unsigned long long startAddress_;
    unsigned long long endAddress_;
};

class MemoryManagement{
    public:
    void setSizeRAM(unsigned long long size);

    //will insert process in processRanges, and return the starting address.
    unsigned long long insertProcessMemory(unsigned long long pSize, int PID);
    bool removeProcessMemory(int PID);

    void refreshHoles();
    void sortProcessRanges();
    void insertRange(processItem newProcess);

    std::vector<processItem> fetchMemoryLayout();
    std::vector<std::pair<unsigned long long, unsigned long long>> fetchMemoryHoles();
    unsigned long long getMemorySize();

    private:
    std::vector<processItem> processRanges_;
    std::vector<std::pair<unsigned long long, unsigned long long>> holeRanges_;
    unsigned long long memorySize_;

};

#endif //_RAM__ 