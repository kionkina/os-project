//Karina Ionkina
#ifndef PCB_H
#define PCB_H

#include "processState.h"
#include <map>
#include <set>
#include <vector>

class PCB {
    public:
        PCB(const int& PID, const int& priority, const long long int &processSize, processState currentState = Ready);
        int getPID();
        int getPriority();
        long long int getSize();
        processState getState();
        void setState(processState state);
        void addWaiting(const long long int &diskNum, const std::vector<requestInfo> &cylinders);
        void removeWaiting(const long long int &diskNum, const long long int &cylinder);
        bool doneWaiting();
        void setRamInfo(ramInfo info);
        ramInfo getRamInfo();
        ~PCB();
    
    private:
        processState currentState;
        ramInfo ram;
        const int PID;
        const int priority;
        const long long int size;
        std::map<long long int, std::set<long long int> > waitMap; 
};

#endif