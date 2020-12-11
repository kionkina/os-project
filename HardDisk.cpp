#include "HardDisk.h"
#include <vector>
#include <iostream>

HardDisk::HardDisk(const long long int &amtDisks) {
    numDisks = amtDisks;
    // indecies correspond to disks
    for (int i=0; i< numDisks; i++) {
        disks.push_back(NULL);
    }
}

long long int HardDisk::getNumDisks(){
    return numDisks;
}

void HardDisk::addDisk(Disk *disk, const int &diskNum){
    disks[diskNum] = disk;
};

Disk* HardDisk::getDisk(const int &diskNum){
    if (diskNum < disks.size()) {
        return disks.at(diskNum);
    }
}

void HardDisk::addRequest(const int &diskNum, const std::vector<requestInfo> &cylinders) {
    // if disk queue is empty, add disk
    if (disks.at(diskNum) == NULL) {
        Disk *disk = new Disk(); 
        addDisk(disk, diskNum);
    }
    
    disks.at(diskNum)->enqueue(cylinders);

    // add disk to busyDisk list
    if (busyDisks.find(diskNum) == busyDisks.end()) {
        busyDisks.insert(diskNum);
    };
    
    return;
}

requestInfo HardDisk::terminateProcess(const int &diskNum) {

    //move head 
    disks.at(diskNum)->moveHead();
    
    //pop cylinder request from disk i/o queue
    requestInfo ret = disks.at(diskNum) -> popCurrent();
    if (ret.pid != -1){
        //If a request was popped, move to next location

        //if that was last track requested for this disk, it becomes idle
        if (isIdle(diskNum)) {
            busyDisks.erase(diskNum);
        }
    }
    return ret;
}

bool HardDisk::isIdle(const int &diskNum) {
    return disks.at(diskNum)->isIdle();
}

void HardDisk::showBusy(){
    std::set<long long int>::iterator it = busyDisks.begin();
    // Iterate till the end of set
    while (it != busyDisks.end())
        {
        const long long int diskNum = (*it);
        Disk* currDisk = disks.at(diskNum);
        std::set<long long int> processes = currDisk->getProcesses();

        // Print disknum and current head
        std::cout << "Disk " << diskNum << ": " << "Reads: " << currDisk->getHead() << " Serves: ";

        for (auto process = processes.begin(); process != processes.end(); ++process) {
            std::cout << ' ' << *process;   
        };
        //Increment the iterator

        std::cout << std::endl;
        it++;
    }

}