#ifndef OPERATINGSYSTEM_H
#define OPERATINGSYSTEM_H

#include "ReadyQueue.h"
#include "PCB.h"
#include "processState.h"
#include "HardDisk.h"
#include "RAM.h"
#include <vector>
#include <string>
#include <map>
#include <set>


class OperatingSystem
{
    private:
        ReadyQueue *RQ;
        PCB *currentProcess;
        HardDisk *hardDisk;
        long long int PIDCtr;
        long long int RAMSize;
        long long int numDisks;
        RAM *memory;
        // {pid: pcb}
        std::map<long long int, PCB*> waitingProcesses;
        
    public:
        OperatingSystem();
        void getData(const std::string prompt, long long int& variable);
        void listen();  
        void createNewProcess(const long long int &priority, const long long int &size);
        void insertProcess(PCB* process);
        void enqueueCylinders(const long long int &diskNum,  const std::vector<requestInfo> &cylinders); 
        void finishReading(const long long int &diskNum);
        void terminate();  
        void showCPUInfo();
        void showHardDiskInfo();
        void showMemoryInfo();
};

#endif   