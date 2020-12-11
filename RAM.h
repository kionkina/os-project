//Karina Ionkina
#ifndef RAM_H
#define RAM_H
#include "PCB.h"
#include "processState.h"
#include <vector>

class RAM {
    public:
        RAM();
        RAM(const long long int &totalMem);
        bool insert(PCB* process);
        void remove(const long long int& pid);
        void print();

    private:
        long long int totalMem;
        std::vector<PCB*> blocks;
        long long int currSize;
};


#endif