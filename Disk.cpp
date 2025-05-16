#include "Disk.h"

void Disks::setDiskCount(int numDisks){
    diskCount_ = numDisks;
    diskJobArray = std::vector<std::vector<FileReadRequest>>(numDisks);
}

void Disks::insertJob(int diskNum, FileReadRequest request){
    if (diskNum > diskCount_) return;
    diskNum -= 1;

    diskJobArray[diskNum].push_back(request);
}

void Disks::finishJob(int diskNum){
    //simulating queue pop
    if (diskNum > diskCount_) return;
    diskNum -= 1;

    if (diskJobArray[diskNum].size() != 0)
        diskJobArray[diskNum].erase(diskJobArray[diskNum].begin());
}

FileReadRequest Disks::getCurrentJob(int diskNum){
    if (diskNum > diskCount_) return;
    diskNum -=1;

    return diskJobArray[diskNum][0];
}

std::queue<FileReadRequest> Disks::getDiskJobs(int diskNum){
    if (diskNum > diskCount_) return {};
    diskNum -= 1;

    std::queue<FileReadRequest> final;
    for(FileReadRequest currentRequest: diskJobArray[diskNum])
        final.push(currentRequest);

    return final;
}