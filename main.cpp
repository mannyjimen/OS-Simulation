// #include <iostream>
#include "SimOS.h"

void testPremptiveScheduling(SimOS& mainOS){

    mainOS.NewProcess(1'000, 3); //PID 2, priority 3
    mainOS.NewProcess(1'000, 2); //PID 3, priority 2
    mainOS.printReadyQueue(); // should print "2 - 3 - 1 -"
    mainOS.NewProcess(1'000, 5); //PID 4, priority 5
    mainOS.printReadyQueue(); //should print "4 - 2 - 3 - 1"
}

void testMemoryManagement(SimOS& mainOS){
    mainOS.NewProcess(100'000, 1);
    mainOS.SimExit();
    mainOS.NewProcess(1, 4);
    mainOS.NewProcess(1'500'400, 5);
    mainOS.NewProcess(200'000, 4);
    mainOS.SimExit();
    mainOS.printMemoryLayout();
    mainOS.NewProcess(300'000, 3);
    mainOS.printMemoryHoles();
}

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
    
    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();
    
    mainOS.DiskReadRequest(7, "charlie"); //PID 3 reqs this, disk 2 (doesnt work)
    mainOS.DiskReadRequest(1, "beta"); //PID 3 wants this disk 1
    
    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();

    mainOS.DiskJobCompleted(1);
    

    mainOS.NewProcess(300, 5); //PID 4
    mainOS.DiskReadRequest(2, "delta"); //PID 4 reqs this on disk 2.

    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();
    
}

void testDiskCascading(SimOS& mainOS){
    
    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();
    mainOS.SimFork(); //PID 4 spawns, 4 is child of 2.
    mainOS.SimFork(); //PID 5 spawns, 5 is child of 2.
    mainOS.SimFork(); //PID 6 spawns, 6 is child of 2.
    mainOS.SimFork(); //PID 7 spawns, 7 is child of 2.
    mainOS.DiskReadRequest(2, "parentrequest"); //PID 2 req

    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();

    mainOS.DiskReadRequest(3, "childrequest"); //PID 4 req
    mainOS.DiskReadRequest(4, "childrequest"); //PID 5 req
    mainOS.DiskReadRequest(5, "childrequest"); //PID 6 req
    mainOS.SimFork(); //PID 7 child , PID 8
    mainOS.DiskReadRequest(1, "childrequest"); //PID 7 req
    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();   

    mainOS.DiskJobCompleted(2); //returned 2 to ready queue 
    mainOS.SimExit();
    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();
    mainOS.SimExit();
    mainOS.SimExit(); //2 gets deleted, 4, 5, 6, and 7 should be deleted as well.

    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();
    
}

void testProcessCascading(SimOS& mainOS){
    mainOS.SimFork(); //PID 4 (child of 2)
    mainOS.printReadyQueue();

    mainOS.SimExit(); // 2 terminated, 4 should terminate as well.
    
    mainOS.printReadyQueue();
}

void testOSIgnore(SimOS& mainOS){
    mainOS.SimExit();
    mainOS.SimExit();
    mainOS.SimExit();
    mainOS.SimExit();
    mainOS.SimWait();
    mainOS.SimFork();
    mainOS.DiskReadRequest(1, "simple request");

    mainOS.printDisksAndJobs();
    mainOS.printReadyQueue();
    mainOS.printMemoryLayout();
    mainOS.printMemoryHoles();
}

void SimWaitTesting(SimOS& mainOS){
    mainOS.printReadyQueue();
    mainOS.SimFork();
    mainOS.printReadyQueue();
    mainOS.SimWait();
    mainOS.printReadyQueue();
    mainOS.SimExit(); //2 should return to the ready queue.
    mainOS.printReadyQueue();
}

void testNoSpaceProcess(SimOS& mainOS){
    mainOS.NewProcess(1'500'000, 5);
    mainOS.printMemoryLayout();
    mainOS.printMemoryHoles();
    mainOS.SimFork(); //PID 4 spawns, 4 is child of 2.
    mainOS.SimFork(); //PID 5 spawns, 5 is child of 2.
    mainOS.SimFork(); //PID 6 spawns, 6 is child of 2.
    mainOS.SimFork(); //PID 7 spawns, 7 is child of 2.
    if(!mainOS.SimFork()){
        std::cout << "process does not fit\n";
    }
    else{
        std::cout << "process fits\n";
    }
    mainOS.printMemoryHoles();
}

void testCascadeMemory(SimOS& mainOS){
    mainOS.NewProcess(100'000, 5); //pid 4
    mainOS.printMemoryLayout();
    mainOS.SimFork();
    mainOS.SimFork();
    mainOS.SimFork();
    mainOS.SimFork();
    mainOS.printMemoryLayout();
    mainOS.printMemoryHoles();
    mainOS.printReadyQueue();
    mainOS.SimExit();
    mainOS.printMemoryLayout();
    mainOS.printMemoryHoles();
    mainOS.printReadyQueue();
}

void testSimWaitAlreadyZomb(SimOS& mainOS){
    //2 creates 4, 2 goes away, 4 exits, 2 comes back, 2 waits, 2 should stay in CPU and not wait.
    mainOS.SimFork(); //creates 4
    mainOS.SimFork(); //creates 5
    mainOS.SimFork(); //creates 6
    mainOS.printReadyQueue();
    mainOS.DiskReadRequest(2, "hello"); //2 goes away
    mainOS.printReadyQueue();
    mainOS.SimExit();
    mainOS.SimExit(); //pid 2 has 2 zombie children
    mainOS.DiskJobCompleted(2);
    mainOS.printReadyQueue();
    mainOS.SimWait();
    mainOS.SimWait(); //2 still here
    mainOS.printReadyQueue(); 
    mainOS.SimWait(); //2 has 6, finally leaves
    mainOS.printReadyQueue(); 
}
int main()
{
    SimOS mainOS(5, 5'000'000, 3'000'000); // PID 1

    mainOS.NewProcess(1'000, 2); //PID 2, priority 3
    mainOS.NewProcess(1'000, 3); //PID 3, priority 2

    //base processes
    testDiskManagement(mainOS);
    // testDiskCascading(mainOS);
    // testForkAndWait(mainOS);
    // testOSIgnore(mainOS);

}