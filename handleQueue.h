#ifndef QUEUES_H
#define QUEUES_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "Node.h"

struct Queue {
    Node* head = nullptr;
    Node* tail = nullptr;
};

inline std::map<std::string, Queue*> queues;

bool isQueueEmpty(Queue *&queue);
bool isQueueNamedInvalid(const std::string &name);
void qpush(std::stringstream &ss);
void qpop(std::stringstream &ss);
void qfront(std::stringstream &ss);
void qprint(std::stringstream &ss);
#endif