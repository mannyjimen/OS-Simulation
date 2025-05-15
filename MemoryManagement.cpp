#include "MemoryManagement.h"

void MemoryManagement::setSizeRAM(unsigned long long size){
    memorySize_ = size;
    holeRanges_.push_back({0, memorySize_});
}

//returns size of memory if no hole is big enough
unsigned long long MemoryManagement::insertProcessMemory(unsigned long long pSize, int PID){
    processItem newProcess;
    newProcess.PID_ = PID;
    newProcess.startAddress_ = memorySize_; //in case no hole is big enough

    if (pSize > memorySize_){
        return memorySize_;
    }

    else{
        unsigned long long optimalDifference = 0;
        unsigned long long optimalStartAddress = memorySize_;

        for(std::pair<unsigned long long, unsigned long long> hole: holeRanges_){
            unsigned long long sizeOfHole = hole.second - hole.first;
            if(pSize > sizeOfHole) continue; //hole is too small for process.
            
            unsigned long long difference = sizeOfHole - pSize;
            
            if(difference > optimalDifference){
                optimalDifference = difference;
                optimalStartAddress = hole.first;
            }
        }
        newProcess.startAddress_ = optimalStartAddress;
    }
    if (newProcess.startAddress_ != memorySize_){ //found a spot
        newProcess.endAddress_ = newProcess.startAddress_ + pSize;
        insertRange(newProcess);
        //adding element to back messes up order.
        refreshHoles();
    }
    return newProcess.startAddress_; //returns size of memory if no place was found
    // insertRange({1, 1, 1});
    // return 1;
}

bool MemoryManagement::removeProcessMemory(int PID){
    for(std::vector<processItem>::iterator it = processRanges_.begin(); it != processRanges_.end(); it++){
        if(it->PID_ == PID){
            processRanges_.erase(it);
            sortProcessRanges(); //removing element doesn't mess up order
            refreshHoles();
            return true;
        }
    }
    return false;
}

void MemoryManagement::insertRange(processItem newProcess){
    processRanges_.push_back(newProcess);
}

void MemoryManagement::sortProcessRanges(){
    //nice little insertion sort implementation
}

void MemoryManagement::refreshHoles(){
    
    holeRanges_.clear();
    unsigned long long temp = 0;
    for(int i = 0; i < processRanges_.size(); i++){
        processItem currProcess = processRanges_[i];
        if(temp >= currProcess.startAddress_ && temp <= currProcess.endAddress_){
            temp = currProcess.endAddress_ + 1;
            continue;
        }
        holeRanges_.push_back({temp, currProcess.startAddress_ - 1});
        temp = currProcess.endAddress_ + 1;
    }
    if(temp < memorySize_)
        holeRanges_.push_back({temp, memorySize_});
}


std::vector<processItem> MemoryManagement::fetchMemoryLayout(){
    return processRanges_;
}

//print holes helper function
std::vector<std::pair<unsigned long long, unsigned long long>> MemoryManagement::fetchMemoryHoles(){
    return holeRanges_;
}
