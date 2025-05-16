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

int main()
{
    SimOS mainOS(5, 5'000'000, 1'000'000); // PID 1
    mainOS.NewProcess(2'000, 3);
    mainOS.NewProcess(2'000, 4);
    mainOS.NewProcess(3'000, 1);
    mainOS.NewProcess(4'000, 2);
    mainOS.NewProcess(5'000, 6);
    mainOS.SimExit();
    mainOS.NewProcess(7'000, 9);
    mainOS.NewProcess(1'000, 1);
    mainOS.NewProcess(2'000, 2);
    mainOS.SimExit();

    // mainOS.printReadyQueue();
    // mainOS.printMemoryLayout();
    // mainOS.printMemoryHoles();
    // testForkAndWait(mainOS);
    
}