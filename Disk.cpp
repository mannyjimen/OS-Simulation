#include "Disk.h"

void Disks::setDiskCount(int numDisks){
    diskCount_ = numDisks;
    diskJobArray = std::vector<std::vector<FileReadRequest>>(numDisks);
}

void Disks::insertJob(int diskNum, FileReadRequest request){
    if (diskNum > diskCount_ || diskNum <= 0) return;
    diskNum -= 1;

    diskJobArray[diskNum].push_back(request);
}

int Disks::finishJob(int diskNum){
    //simulating queue pop
    if (diskNum > diskCount_ || diskNum <= 0) return -1;
    diskNum -= 1;

    int finishedProcess{-1};
    if (diskJobArray[diskNum].size() != 0){
        finishedProcess = diskJobArray[diskNum][0].PID;
        diskJobArray[diskNum].erase(diskJobArray[diskNum].begin());
    }
    return finishedProcess;
}

FileReadRequest Disks::getCurrentJob(int diskNum){
    FileReadRequest empty;
    if (diskNum > diskCount_ || diskNum <= 0) {
        return empty;
    }
    diskNum -=1;

    if (diskJobArray[diskNum].size() > 0)
        return diskJobArray[diskNum][0];
    return empty;
}

std::queue<FileReadRequest> Disks::getDiskJobs(int diskNum){
    if (diskNum > diskCount_ || diskNum <= 0) return {};
    diskNum -= 1;

    std::queue<FileReadRequest> final;
    for(FileReadRequest currentRequest: diskJobArray[diskNum])
        final.push(currentRequest);
    if(final.size() >= 1) final.pop();
    return final;
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
    return diskCount_;
}