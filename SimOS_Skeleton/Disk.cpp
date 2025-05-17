#include "Disk.h"

void Disks::setDiskCount(int numDisks){
    diskCount_ = numDisks;
    std::vector<std::vector<FileReadRequest>> res(numDisks);
    diskJobArray = res;
}

void Disks::insertJob(int diskNum, FileReadRequest request){
    if (diskNum >= diskCount_ || diskNum <= 0) return;

    diskNum-=1;

    diskJobArray[diskNum].push_back(request);
}

void Disks::finishJob(int diskNum){
    // simulating queue pop


    if (diskNum > diskCount_ || diskNum <= 0) return;
    diskNum -= 1;

    if (diskJobArray[diskNum].size() != 0)
        diskJobArray[diskNum].erase(diskJobArray[diskNum].begin());
}

FileReadRequest Disks::getCurrentJob(int diskNum){
    if (diskNum > diskCount_ || diskNum <= 0) {
        FileReadRequest empty;
        return empty;
    }
    diskNum -=1;

    return diskJobArray[diskNum][0];

    // FileReadRequest fin;
    // return fin;
}

std::queue<FileReadRequest> Disks::getDiskJobs(int diskNum){
    
    std::queue<FileReadRequest> final;
    if (diskNum > diskCount_ || diskNum <= 0){
        return final;
    }
    diskNum -= 1;

    for(FileReadRequest currentRequest: diskJobArray[diskNum])
        final.push(currentRequest);

    return final;
    
    
    // std::queue<FileReadRequest> fin;
    // return fin;
}

void Disks::removeDiskJobs(int PID){
    for(std::vector<FileReadRequest> &currDiskJobs: diskJobArray){
        for(std::vector<FileReadRequest>::iterator requestIt = currDiskJobs.begin(); requestIt != currDiskJobs.end(); requestIt++){
            if (requestIt->PID == PID){
                requestIt = currDiskJobs.erase(requestIt) - 1;
            }
        }
    }
}

int Disks::getDiskCount(){
    // return 0;
    return diskCount_;
}