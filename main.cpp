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
    SimOS mainOS(5, 1'000'000, 5'000'000); // PID 1
    mainOS.NewProcess(1'000'000, 2); //PID 2
    mainOS.NewProcess(2'000, 1); // PID 3
    mainOS.NewProcess(2'000, 6); // PID 4
    mainOS.NewProcess(2'000, 2); // PID 5

    testForkAndWait(mainOS);
}