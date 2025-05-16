#ifndef _DISK_
#define _DISK_

#include <vector>
#include <queue>

struct FileReadRequest
{
    int  PID{0};
    std::string fileName{""};
};

class Disks{
    public:
    void setDiskCount(int numDisks);
    void insertJob(int diskNum, FileReadRequest request);
    void finishJob(int diskNum);
    FileReadRequest getCurrentJob(int diskNum);
    std::queue<FileReadRequest> getDiskJobs(int diskNum);

    void removeDiskJobs(int PID);

    private:
    int diskCount_;
    std::vector<std::vector<FileReadRequest>> diskJobArray;
    
};  

#endif //_DISK__