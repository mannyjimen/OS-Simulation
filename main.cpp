#include <iostream>
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
    mainOS.NewProcess(100, 1); //PID 1
    mainOS.NewProcess(200, 3); //PID 2
    
    std::cout << "All Disk Jobs before additions\n";
    mainOS.printDisksAndJobs();
    

    mainOS.DiskReadRequest(2, "charlie");
    mainOS.DiskReadRequest(1, "beta");
    mainOS.DiskReadRequest(1, "wukong");
    
    std::cout << "All Disk Jobs after PID 2 insertions\n";
    mainOS.printDisksAndJobs();
    
    mainOS.NewProcess(300, 5);
    mainOS.SimExit();
    mainOS.DiskReadRequest(2, "delta");
    mainOS.DiskReadRequest(4, "epsilon");
    std::cout << "All Disk Jobs after SimExit (erase pid2) and new requests\n";
    mainOS.printDisksAndJobs();
    
}

int main()
{
    SimOS mainOS(5, 5'000'000, 1'000'000); // PID 1
    
    // mainOS.printReadyQueue();
    // mainOS.printMemoryLayout();
    // mainOS.printMemoryHoles();
    // testForkAndWait(mainOS);
    testDiskManagement(mainOS);
}