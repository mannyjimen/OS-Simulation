## Operating System Simluation
Implemented a working OS simulator, which can perform the following operations.

**Processor/Process Functionality**
- Ready Queue using priority scheduling.
- Create new process.
- FORK existing process.
- Call WAIT on current process, which will wait for a the process's child to terminate before joining the READY state.
- EXIT the current process.

**Memory/RAM Functionality**
- Implemented "Worst-Fit" memory alignment.
- No real physical memory usage for RAM simulation, using ranges for process memory.

**Disk Functionality**
- I/O queue using first-come first-serve scheduling.
- Can have various disks each with seperate I/O queues.
