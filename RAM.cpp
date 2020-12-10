#include "RAM.h"
#include <vector>
#include <iostream>
// your program should simulate contiguous memory management with “First-fit” approach.

// Need default constructor for declaration in OS header
RAM::RAM(): totalMem() {};

//Overloaded constructor for initialization after retreiving RAM size
RAM::RAM(const long long int &size): totalMem(size), currSize(0) {};

//places process into blocks vector 
bool RAM::insert(PCB* process) {
    long long int pSize = process->getSize();

    //RAM has no room for process of this size
    if (currSize + pSize > totalMem) {
        std::cout << "1" << std::endl;
        return false;
    }

    //if no blocks are used up and the size is ok, just add it 
    if (blocks.size() == 0) { 
        if (pSize <= totalMem) {
                ramInfo info = {0, pSize - 1};
                process->setRamInfo(info);
                blocks.push_back(process);
                return true;
            }
        return false;
    }

    PCB* currProcess = blocks.at(0);
    ramInfo prevBlock = currProcess->getRamInfo();
    std::cout << "3" << std::endl;
    
    //using iterators because vector insert pos is of type it
    for (std::vector<PCB*>::iterator it =blocks.begin() + 1; it != blocks.end(); it++) {
        PCB* currProcess = *it;
        ramInfo currBlock = currProcess->getRamInfo();
        
        //Block with size greater than process size found, add process
        if (currBlock.startPos - prevBlock.endPos >= pSize) {
            ramInfo newBlock = {prevBlock.endPos + 1, prevBlock.endPos + pSize};
            process->setRamInfo(newBlock);
            blocks.insert(it, process);
            currSize += pSize;
            return true;
        };
        prevBlock = currBlock;
    };

    //at this point prevBlock = last block
    if (totalMem - prevBlock.endPos >= pSize) {
        std::cout << "4" << std::endl;
        ramInfo newBlock = {prevBlock.endPos + 1, prevBlock.endPos + pSize};
        process->setRamInfo(newBlock);
        blocks.push_back(process);
        currSize += pSize;
        return true;
    }

}

void RAM::remove(const long long int& pid) {
    for (std::vector<PCB*>::iterator it = blocks.begin() + 1; it != blocks.end(); it++) {
        if ((*it)->getPID() == pid) {
            std::cout << "found process in blocks, about to remove..." << std::endl;
            blocks.erase(it);
            return;
        }
        else {
            std::cout << "process not found" << std::endl;
            return;
        }
    }
}

void RAM::print() {
    std::cout <<"RAM usage: " << std::endl;
    for (PCB* block: blocks) {
        ramInfo currInfo = block->getRamInfo();
        std::cout << currInfo.startPos << " - " << currInfo.endPos << ": " << block->getPID() << std::endl;
    }


}

