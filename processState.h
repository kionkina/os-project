
#ifndef PROCESSSTATE_H
#define PROCESSSTATE_H

struct requestInfo {
    long long int track;
    long long int pid;
};

struct ramInfo {
    long long int startPos;
    long long int endPos;
};


enum processState {Ready, Waiting, Running, Halted, Terminated}; 


#endif