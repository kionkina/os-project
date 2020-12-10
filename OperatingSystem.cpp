#include "OperatingSystem.h"
#include "PCB.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <map>

using namespace std;

OperatingSystem::OperatingSystem() { 
    PIDCtr = 1;
    currentProcess = NULL;
    RQ = new ReadyQueue;
    const string RAMPrompt = "How much RAM memory is there on the simulated computer?";
    const string diskPrompt = "How many hard disks does the simulated computer have?";

    getData(RAMPrompt, RAMSize);
    getData(diskPrompt, numDisks);

    hardDisk = new HardDisk(numDisks);
    memory = new RAM(RAMSize);
    listen();
};

void OperatingSystem::getData(std::string prompt, long long int& variable) {
    std::cout << prompt << std::endl;
    string input;
    while(getline(std::cin, input)) {
        try {
            // if input is not a valid num, the exception will be ~caught~
            // stoll for discards whitespaces
            // if input includes a letter, only the numbers preceding it will count
            variable = stoll(input);
            return;
        } catch(const std::exception& e) {
            std::cout << "Enter a valid number pls." << std::endl;
        }
    }
}


void OperatingSystem::listen() {
    std::string input, temp;
    std::vector<std::string> curr_inputs;
    std::stringstream ss;
    
    std::cout << "Listening for commands now. " << std::endl;

    // listen for line
    while (getline(std::cin, input)){
        ss << input;

        while(!ss.eof()) {
            // store each token, separated by spaces, in temp
            ss >> temp;

            if (temp.length() > 0) {
                curr_inputs.push_back(temp);
            }    
        }

        // line has been processed
        if (!curr_inputs.empty() && curr_inputs.at(0).length() == 1) {
            try {
                // string is not integral so compare first char
                switch (curr_inputs.at(0)[0])
                {
                case 'A':
                    createNewProcess(stoll(curr_inputs.at(1)), stoll(curr_inputs.at(2)));
                    break;
                
                case 'd':
                {
                    // only add if there is a process using CPU
                    if (!currentProcess == NULL) {
                        std::vector<requestInfo> cylinders;
                        for(int i=2; i < curr_inputs.size(); i++){
                            requestInfo input;
                            input.pid = currentProcess->getPID();
                            input.track = stoll(curr_inputs.at(i));
                            cylinders.push_back(input);
                        };
                        enqueueCylinders(stoll(curr_inputs.at(1)), cylinders);
                    }
                    else {
                        std::cout << "No process running..." << std::endl;
                    }
                    break;
                }
                case 'D':
                    finishReading(stoll(curr_inputs.at(1)));
                    break;

                case 'S':
                {
                    std::string secondInput = curr_inputs.at(1);
                    if (secondInput == "r")
                    {
                        cout << "running show cpu info " << endl;
                        showCPUInfo();
                    }
                    else if (secondInput == "i" )
                    {
                        showHardDiskInfo();
                    }
                    else if (secondInput == "m")
                    {
                        showMemoryInfo();
                    }
                    break;
                }
                case 't':
                    terminate();
                    break;

                default:
                    break;
                }
            } catch (const std::exception& e){
                cout << "Please check your input." << endl;
            }

        } else {
            cout << "Try again pls..." << endl;
        }

        // Here we go again! Weeeee
        curr_inputs.clear();
        ss.clear();
        temp.clear();

    }

    return;
};

void OperatingSystem::createNewProcess(const long long int &priority, const long long int &size) {
    PCB *newProcess = new PCB(PIDCtr, priority, size);
    PIDCtr++;
    insertProcess(newProcess);
    return;
};

void OperatingSystem::insertProcess(PCB* process) {
    int priority = process->getPriority();
    if (currentProcess != NULL) {
            if (priority > currentProcess->getPriority()) {
            //do preemprive thangs
                currentProcess->setState(Halted);
                RQ->pushFront(currentProcess);
                process->setState(Running);
                currentProcess = process;
            }
            else {
                // priority is less than current, just insert it
                RQ->insert(process);
                process->setState(Ready);
            }
        }
        else {
            currentProcess = process;
            process->setState(Running);
        }

    memory->insert(process); 
    std::cout << "Added process with pid " << process->getPID() << std::endl;
}

void OperatingSystem::enqueueCylinders(const long long int &diskNum,  const std::vector<requestInfo> &cylinders) {
    cout << "in RC: " << "disk: " << diskNum << endl;
    if (diskNum > hardDisk->getNumDisks()-1 || cylinders.empty()) {
        std::cout << "Invalid disk num or empty list" << std::endl;
        return;
    }

    // add these cylinders to the disk queue
    hardDisk->addRequest(diskNum, cylinders);

    // add cylinders and disk to process
    currentProcess->addWaiting(diskNum, cylinders);
    currentProcess->setState(Waiting);

    //add process to waiting processes
    waitingProcesses[currentProcess->getPID()] = currentProcess;

    //get next process from ready queue, use CPU
    if (RQ->isEmpty()) {
        currentProcess = NULL;
    }
    else {
        currentProcess = RQ->popFront();
        currentProcess->setState(Running);
    }
};

void OperatingSystem::finishReading(const long long int &diskNum) {
    cout << "in finishReading: " << diskNum << endl;
    if (diskNum > hardDisk->getNumDisks()-1) {
        std::cout << "Invalid disk num" << std::endl;
        return;
    }
    
    //ask hdd to pop cylinder request 
    requestInfo terminated = hardDisk->terminateProcess(diskNum);

    if (terminated.pid == -1) {
        std::cout << "No cylinder is being read atm" << std::endl;
        return;
    }
   
    // Finish reading track, update PCB
    PCB *process = waitingProcesses[terminated.pid];
    std::cout << "removing waiting from process... " << std::endl;
    process->removeWaiting(diskNum, terminated.track);
    
    if (process->doneWaiting()) {
        waitingProcesses.erase(terminated.pid);
        
        insertProcess(process);
        std::cout << "removed " << terminated.pid << " from waiting process";
    }


};


void OperatingSystem::terminate() {

    if (currentProcess != NULL) {
        //TODO: make sure this works with deallocation
        currentProcess->setState(Terminated);
        memory->remove(currentProcess->getPID());

        //TODO: deallocate PCB
        if (!RQ->isEmpty()) {
            currentProcess = RQ->getFront();
            
            RQ->popFront();
            currentProcess->setState(Running);
        } else {
            // that was the last process in the queue. Idle 
            currentProcess = NULL;
            return;
        }

    } else {
        cout << "There's no process to terminate!" << endl;
        return;
    }

}

void OperatingSystem::showCPUInfo() {
    if (currentProcess != NULL) {
        cout << "Current process PID: " << currentProcess->getPID() << endl;
        RQ->print();
    } else {
        cout << "No process is running" << endl;
    }

};

void OperatingSystem::showHardDiskInfo() {
    std::cout << "Busy Disks: " << std::endl;
    hardDisk->showBusy();
};

void OperatingSystem::showMemoryInfo() {
    memory->print();
};