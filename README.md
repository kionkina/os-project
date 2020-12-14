## Operating System Simulation for CSCI3400

This is a command-based simulation of an OS with pre-emptive priority CPU scheduling, shortest seek first I/O queues, and first-fit contiguous memory management for Prof. Shostak's OS course (Fall '20).

### Usage
```
make prog
./prog
```
#### Commands accepted by OS:
* **A prioritySize**: ‘A’ input means that a new common process has been created. When the new process arrives, your program should create its PCB and place the process in the ready-queue or the CPU. The requested amount of memory should be allocated for the new process
* **t**:   currently running process terminates
* **d  disk_number cylinders...**: The process that currently uses the CPU requests the hard disk #number. For example, the command d 0 2 5 18 means that the currently running process wants to read from the cylinders 2, 5, and 18 from the disk 0.
* **D  disk_number**: The hard disk #number has finished reading a cylinder.
* **S r**: Shows what process is currently using the CPU and what processes are waiting in the ready-queue.
* **S i**: Shows what processes are currently using the hard disks and what processes are waiting to use them. For each busy hard disk show the process that uses it and show its I/O-queue. The enumeration of hard disks starts from 0.
* **S m**: Shows the state of memory. Show the range of memory addresses used by each process in the system.
