#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

#include "handleArray.h"
#include "handleLinkedList.h"
#include "handleDoubleLinkedList.h"
#include "handleQueue.h"
#include "handleStack.h"
#include "handleAVLTree.h"

void loadFromFile(const std::string& filename);
void saveToFile(const std::string& filename);

void executeArrayCommand(const std::string &command, std::stringstream &ss);
void executeLinkedListCommand(const std::string &command, std::stringstream &ss);
void executeDLinkedListCommand(const std::string &command, std::stringstream &ss);
void executeStackCommand(const std::string &command, std::stringstream &ss);
void executeQueueCommand(const std::string &command, std::stringstream &ss);
#endif