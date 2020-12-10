#ifndef READYQUEUE_H
#define READYQUEUE_H

#include "PCB.h"
#include <functional>
#include <list>

struct Node
  {
    PCB *process;
    Node *next;
  };	
  

class ReadyQueue {

    private:   
      Node *head;

    
    public:
      ReadyQueue();
      void insert(PCB *process);
      PCB* popFront();
      // we could just use insert
      void pushFront(PCB *process);
      bool isEmpty();
      PCB* getFront();
      void print();
};

#endif