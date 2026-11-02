#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include "Node.h"

inline std::map<std::string, Node*> linkedLists;
bool isLLEmpty(Node *&ll);
bool isLinkedListNamedInvalid(const std::string& name);

void faddBeg(std::stringstream &ss);
void faddEnd(std::stringstream &ss);
void faddAfter(std::stringstream &ss);
void faddBefore(std::stringstream &ss);
void fdelBeg(std::stringstream &ss);
void fdelEnd(std::stringstream &ss);
void fdelAfter(std::stringstream &ss);
void fdelBefore(std::stringstream &ss);
void fdelVal(std::stringstream &ss);
void fGet(std::stringstream &ss);
void fPrint(std::stringstream &ss);
void fgetBeg(std::stringstream &ss);
void fgetEnd(std::stringstream &ss);
#endif