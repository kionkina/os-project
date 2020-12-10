#ifndef HARD_DISK_H
#define HARD_DISK_H

#include "Disk.h"
#include "processState.h"
#include "RAM.h"
#include <set>
#include <vector>

class HardDisk {
    private:
        long long int numDisks;
        void addDisk(Disk *disk, const int &diskNum);
        bool isIdle(const int &disNum);
        std::vector<Disk*> disks;
        std::set<long long int> busyDisks;
        RAM memory;
        
    public:
        HardDisk(const long long int &numDisks);
        long long int getNumDisks();
        Disk* getDisk(const int &diskNum);
        void addRequest(const int &diskNum, const std::vector<requestInfo> &cylinders);
        requestInfo terminateProcess(const int &diskNum);
        void showBusy();
};

#endif