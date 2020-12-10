#ifndef DISK_H
#define DISK_H

#include <vector>
#include "processState.h"

class Disk {
    private:
        // track, PID 
        std::vector<requestInfo> diskQueue;
        int head;
        int val;
        int getDistance(int cylinder);
    public:
        Disk(); 
        void enqueue(const  std::vector<requestInfo> &cylinders);
        requestInfo popCurrent();
        void moveHead();
        bool isIdle();
};

#endif