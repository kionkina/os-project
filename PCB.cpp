#include "PCB.h"
#include "processState.h"

#include <vector>
#include <iostream>

// initialize PID, priority, currentState with initializer list
PCB::PCB(const int& PID, const int& priority, const long long int &processSize, processState currentState) 
    : PID(PID), priority(priority), size(processSize), currentState(currentState) {};


int PCB::getPID(){
    return PID;
}

int PCB::getPriority(){
    return priority;
}

processState PCB::getState() {
    return currentState;
}

void PCB::setState(processState state) {
    currentState = state;
}

void PCB::addWaiting(const long long int &diskNum, const std::vector<requestInfo> &cylinders){
    if (waitMap.find(diskNum) != waitMap.end()) {
        for (auto cylinder: cylinders) {
            //std::cout << "adding " << cylinder.track << "to set" << std::endl;
            waitMap[diskNum].insert(cylinder.track);
        }
    }
    else {
        std::set<long long int> cylinderSet;
         for (auto cylinder: cylinders) {
            //std::cout << "adding" << cylinder.track << " to set " << std::endl;
            cylinderSet.insert(cylinder.track);
        }
        waitMap[diskNum] = cylinderSet;
    }
}

void PCB::removeWaiting(const long long int &diskNum, const long long int &cylinder) {
    //remove track and/or process
    if (waitMap.find(diskNum) != waitMap.end()) {
        waitMap[diskNum].erase(cylinder);
        if (waitMap[diskNum].empty()) {
            waitMap.erase(diskNum);
        }
    }
    else {
        std::cout << "This process is not using disk " << diskNum << std::endl;
    }
}

bool PCB::doneWaiting() {
    return waitMap.empty(); 
}

void PCB::setRamInfo(ramInfo info){
    ram = info;
}

ramInfo PCB::getRamInfo() {
    return ram;
}

long long int PCB::getSize() {
    return size;
}