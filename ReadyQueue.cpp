#include "ReadyQueue.h"
#include <iostream>

ReadyQueue::ReadyQueue() : head(NULL) {}

void ReadyQueue::insert(PCB *process){
    Node *newNode = new Node;
    newNode->process = process;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
        newNode = NULL;
        return;
    }

    Node *temp = head;
    int currPriority = process->getPriority();
    if (currPriority > temp->process->getPriority()) {
        return pushFront(process);
    }

    while(temp->next != NULL) {
        // if next element is less important, place node in current pos
        std::cout << "temp is " << temp->process->getPID() << std::endl;
        if (currPriority > temp->next->process->getPriority()) {
            std::cout << currPriority << " is bigger than " << temp->next->process->getPriority() << std::endl;
            newNode->next = temp->next;
            temp->next = newNode;
            return;
        }
        else {
            temp = temp->next;
        }
    }
    // reached pre-last element
    temp->next = newNode;
    // delete temp;

    return;
};

PCB* ReadyQueue::popFront() {
    PCB *front = getFront();
    Node *temp = new Node;
    temp = head;
    head = head->next;
    delete temp;

    return front;

};

void ReadyQueue::pushFront(PCB *process) {
    Node *newNode = new Node;
    newNode->process = process;
    newNode->next = NULL;
    
    if (head == NULL) {
        head = newNode;
        newNode = NULL;
        return;
    }

    newNode->next = head;
    head = newNode;
    return;
}

bool ReadyQueue::isEmpty() {
    return head == NULL;
};

PCB* ReadyQueue::getFront() {
    if (head == NULL) {
        return NULL;
    }

    return head->process;
}

void ReadyQueue::print() {
    Node *temp = head;
    if (temp == NULL) {
        std::cout << "No other processes waiting" << std::endl;
        return;
    }

    std::cout << "(PID, Priority): ";
    while (temp != NULL) {
        std::cout << " (" << temp->process->getPID() << ", " << temp->process->getPriority() << ") ";
        temp = temp->next;
    }

    std::cout << std::endl;
}