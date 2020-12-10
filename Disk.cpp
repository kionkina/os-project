#include "Disk.h"
#include <iostream>
#include <climits>

Disk::Disk() : head(0), val(0) { };

void Disk::enqueue(const  std::vector<requestInfo> &cylinders) {
    for (auto cylinder: cylinders)
        diskQueue.push_back(cylinder);
}

requestInfo Disk::popCurrent() {
    if (diskQueue.empty()) {
        requestInfo temp = {-1, -1};
        return temp;
    }
    requestInfo retPair = diskQueue[head];
    std::cout << "reading" << retPair.track << std::endl;

    // remove element from queue
    diskQueue.erase(diskQueue.begin()+head);
    return retPair;
}

void Disk::moveHead() {
    if (diskQueue.empty()){
        std::cout << "no more requests. staying in place" << std::endl;
        return;
    }

    int minDiff = INT_MAX;
    int newHeadPos = head;
    for (int i=0; i < diskQueue.size(); i++){
        int currDiff= getDistance(diskQueue.at(i).track);
        if (currDiff < minDiff) {
            minDiff = currDiff;
            newHeadPos = i;
        }
    }
    val = diskQueue.at(newHeadPos).track;
    head = newHeadPos;
    std::cout << "moved head to " << newHeadPos << std::endl;
    std::cout << "new val is " << val << std::endl;
};

int Disk::getDistance(int cylinder){
    return abs(val - cylinder);
}

bool Disk::isIdle() {
    return diskQueue.empty();
}