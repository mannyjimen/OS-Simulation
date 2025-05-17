// #include <iostream>
#include "SimOS.h"


void testForkAndWait(SimOS& mainOS){
    std::cout << "prefork: ";
    mainOS.printReadyQueue();
    mainOS.SimFork(); 
    std::cout << "postfork: ";
    mainOS.printReadyQueue();
    
    mainOS.SimWait();
    std::cout << "simwait: ";
    mainOS.printReadyQueue();
    
    mainOS.SimExit();
    std::cout << "exited child: ";
    mainOS.printReadyQueue();
}

void testDiskManagement(SimOS& mainOS){
    mainOS.NewProcess(100, 1); //PID 2
    mainOS.NewProcess(200, 3); //PID 3
    
    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();
    
    mainOS.DiskReadRequest(2, "charlie"); //PID 3 reqs this, disk 2
    mainOS.DiskReadRequest(1, "beta"); //PID 2 wants this disk 1
    
    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();

    mainOS.DiskJobCompleted(1);
    

    mainOS.NewProcess(300, 5); //PID 4
    mainOS.DiskReadRequest(2, "delta"); //PID 4 reqs this on disk 2.
    // mainOS.printDisksAndJobs();
    // mainOS.DiskReadRequest(4, "epsilon");

    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();
    
}

int main()
{
    SimOS mainOS(5, 5'000'000, 1'000'000); // PID 1
    testDiskManagement(mainOS);
}