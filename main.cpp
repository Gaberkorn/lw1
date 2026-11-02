//++ main.cpp StorageEngine.h StorageEngine.cpp handleArray.h handleArray.cpp Node.h handleLinkedList.h handleLinkedList.cpp handleDoubleLinkedList.h handleDoubleLinkedList.cpp handleStack.h handleStack.cpp handleQueue.h handleQueue.cpp handleAVLTree.h handleAVLTree.cpp -o final


#include <iostream>
#include <string>
#include <cstring>
#include "StorageEngine.h"

enum class Domain
{
    Array,
    LinkedList,
    DoubleLinkedList,
    Stack,
    Queue,
    Tree,
    Unknown
};

Domain detectDomain(const char &w)
{
    if (w == ' ')
        return Domain::Unknown;
    if (w == 'T')
        return Domain::Tree;
    if (w == 'M')
        return Domain::Array;
    if (w == 'F')
        return Domain::LinkedList;
    if (w == 'L')
        return Domain::DoubleLinkedList;
    if (w == 'S')
        return Domain::Stack;
    if (w == 'Q')
        return Domain::Queue;
    return Domain::Unknown;
}

int main(int argc, char *argv[])
{
    std::string filename = "";
    std::string query = "";

    for (int i = 1; i < argc; i++)
    {
        if (std::strcmp(argv[i], "--file") == 0 && i + 1 < argc)
        {
            filename = argv[++i];
        }
        else if (std::strcmp(argv[i], "--query") == 0 && i + 1 < argc)
        {
            query = argv[++i];
        }
    }

    if (filename.empty() || query.empty())
    {
        std::cerr << "Usage: ./dbms --file <filename> --query '<command>'\n";
        return 1;
    }

    loadFromFile(filename);

    std::stringstream ss(query);
    std::string command;
    std::string name;
    ss >> command;

    Domain domainChoice = detectDomain(query[0]);

    switch (domainChoice)
    {
    case Domain::Array:
        executeArrayCommand(command, ss);
        break;
    case Domain::LinkedList:
        executeLinkedListCommand(command, ss);
        break;
    case Domain::DoubleLinkedList:
        executeDLinkedListCommand(command, ss);
        break;
    case Domain::Stack:
        executeStackCommand(command, ss);
        break;
    case Domain::Queue:
        executeQueueCommand(command, ss);
        break;
    case Domain::Tree:
        executeAVLTreeCommand(command, ss);
        break;
    default:
        break;
    }

    saveToFile(filename);
    return 0;;
}
