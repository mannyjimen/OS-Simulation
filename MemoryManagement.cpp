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

    if (holeRanges_.size() == 1){ //just created, OS should be put in
        if(pSize > memorySize_) return memorySize_; 
        newProcess.startAddress_ = 0;
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

    if(newProcess.startAddress_ != memorySize_){ //found a spot
        newProcess.endAddress_ = newProcess.startAddress_ + pSize;
        processRanges_.push_back(newProcess);

        reOrganizeProcessRanges();
        refreshHoles();
    }
    return newProcess.startAddress_; //returns size of memory if no place was found
}

bool MemoryManagement::removeProcessMemory(int PID){
    for(std::vector<processItem>::iterator it = processRanges_.begin(); it != processRanges_.end(); it++){
        if(it->PID_ == PID){
            processRanges_.erase(it);
            reOrganizeProcessRanges();
            refreshHoles();
            return true;
        }
    }
    return false;
}

void MemoryManagement::reOrganizeProcessRanges(){

}

void MemoryManagement::refreshHoles(){

}