#ifndef STACKS_H
#define STACKS_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "Node.h"

struct Stack {
    Node* head = nullptr;
};

inline std::map<std::string, Stack*> stacks;
bool isStackEmpty(Stack* &stack);
bool isStackNamedInvalid(const std::string &name);
void spush(std::stringstream &ss);
void spop(std::stringstream &ss);
void stop(std::stringstream &ss);
void sprint(std::stringstream &ss);
#endif