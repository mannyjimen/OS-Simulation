#include <iostream>
#include "SimOS.h"

int main()
{
    SimOS mainOS(5, 1'000'000, 5'000'000); // PID 1
    mainOS.NewProcess(1'000'000, 2); //PID 2
    mainOS.NewProcess(2'000, 1); // PID 3
    mainOS.NewProcess(2'000, 6); // PID 4
    mainOS.NewProcess(2'000, 2); // PID 5
    mainOS.printReadyQueue();
    mainOS.SimFork();
    mainOS.printReadyQueue();
    mainOS.SimExit();
    mainOS.printReadyQueue();

    std::cout << mainOS.GetCPU();
}  