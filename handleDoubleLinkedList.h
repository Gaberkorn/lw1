#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include <string>
#include <sstream>
#include <iostream>
#include <map>

struct DLL_Node
{
    std::string data;
    DLL_Node* next;
    DLL_Node* back;
};

struct DLL{
    DLL_Node* head;
    DLL_Node* tail;
};

inline std::map<std::string, DLL*> dLinkedLists;
bool isDLLEmpty(DLL *&ll);
bool isDLLNamedInvalid(const std::string& name);
void executeDLinkedListCommand(const std::string& command, std::stringstream& ss);

void laddBeg(std::stringstream &ss);
void laddEnd(std::stringstream &ss);
void laddAfter(std::stringstream &ss);
void laddBefore(std::stringstream &ss);
void ldelBeg(std::stringstream &ss);
void ldelEnd(std::stringstream &ss);
void ldelAfter(std::stringstream &ss);
void ldelBefore(std::stringstream &ss);
void ldelVal(std::stringstream &ss);
void lGet(std::stringstream &ss);
void lPrint(std::stringstream &ss);
void lgetBeg(std::stringstream &ss);
void lgetEnd(std::stringstream &ss);
#endif