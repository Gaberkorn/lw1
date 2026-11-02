#include "handleLinkedList.h"

bool isLLEmpty(Node *&ll)
{
    if (ll == nullptr)
    {
        std::cout << "Error: Linked list is empty!\n";
        return true;
    }
    else
        return false;
}

bool isLinkedListNamedInvalid(const std::string &name)
{
    if (linkedLists.find(name) == linkedLists.end() || linkedLists[name] == nullptr)
    {
        std::cout << "Error: Linked list '" << name << "' doesn't exist!\n";
        return true;
    }
    return false;
}

void faddBeg(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;

    if (ss.fail())
        return;

    linkedLists[name] = new Node{value, linkedLists[name]};
}

void faddEnd(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;

    if (ss.fail())
        return;

    Node *newNode = new Node{value, nullptr};
    if (linkedLists.find(name) == linkedLists.end() || linkedLists[name] == nullptr)
    {
        linkedLists[name] = newNode;
    }
    else
    {
        Node *currentNode = linkedLists[name];
        while (currentNode->next != nullptr)
        {
            currentNode = currentNode->next;
        }
        currentNode->next = newNode;
    }

    std::cout << value << "\n";
}

void faddAfter(std::stringstream &ss)
{
    std::string name;
    std::string value;
    std::string newData;
    ss >> name >> value >> newData;

    if (ss.fail())
        return;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];
    if (isLLEmpty(myLinkedList))
        return;

    Node *currentNode = myLinkedList;

    while (currentNode != nullptr && currentNode->data != value)
    {
        currentNode = currentNode->next;
    }

    if (currentNode != nullptr)
    {
        Node *newNode = new Node{newData, currentNode->next};
        currentNode->next = newNode;
        std::cout << newData << "\n";
    }
    else
    {
        std::cout << "Error: Element not found!\n";
    }
}

void faddBefore(std::stringstream &ss)
{
    std::string name;
    std::string value;
    std::string newData;
    ss >> name >> value >> newData;
    if (ss.fail())
        return;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];
    if (isLLEmpty(myLinkedList))
        return;

    Node *currentNode = myLinkedList;
    Node *beforeCurrentNode = nullptr;

    while (currentNode != nullptr && currentNode->data != value)
    {
        beforeCurrentNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)
    {
        std::cout << "Error: Element not found!\n";
    }
    else if (currentNode == myLinkedList)
    {
        linkedLists[name] = new Node{newData, myLinkedList};
    }
    else
    {
        Node *newNode = new Node{newData, currentNode};
        beforeCurrentNode->next = newNode;
    }

    std::cout << newData << "\n";
}

void fdelBeg(std::stringstream &ss)
{
    std::string name;
    ss >> name;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];
    if (isLLEmpty(myLinkedList))
        return;

    Node *deleteNode = myLinkedList;
    linkedLists[name] = myLinkedList->next;
    std::cout << deleteNode->data << "\n";
    delete deleteNode;
}

void fdelEnd(std::stringstream &ss)
{
    std::string name;
    ss >> name;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];
    if (isLLEmpty(myLinkedList))
        return;

    if (myLinkedList->next == nullptr)
    {
        std::cout << myLinkedList->data << "\n";
        delete myLinkedList;
        linkedLists[name] = nullptr;
    }
    else
    {
        Node *currentNode = nullptr;
        Node *beforeCurrentNode = nullptr;
        currentNode = myLinkedList;
        while (currentNode->next != nullptr)
        {
            beforeCurrentNode = currentNode;
            currentNode = currentNode->next;
        }
        beforeCurrentNode->next = nullptr;
        std::cout << currentNode->data << "\n";
        delete currentNode;
    }
}

void fdelAfter(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];
    if (isLLEmpty(myLinkedList))
        return;

    Node *currentNode = myLinkedList;

    while (currentNode != nullptr && currentNode->data != value)
    {
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)
    {
        std::cout << "Error: Element not found!\n";
    }
    else if (currentNode->next == nullptr)
    {
        std::cout << "Error: No element after it!\n";
    }
    else
    {
        Node *deleteNode = currentNode->next;
        currentNode->next = deleteNode->next;
        std::cout << deleteNode->data << "\n";
        delete deleteNode;
    }
}

void fdelBefore(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];
    if (isLLEmpty(myLinkedList))
        return;

    Node *currentNode = myLinkedList;
    Node *beforeCurrentNode = nullptr;
    Node *beforeBefore = nullptr;

    while (currentNode != nullptr && currentNode->data != value)
    {
        beforeBefore = beforeCurrentNode;
        beforeCurrentNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)
    {
        std::cout << "Error: Element not found!\n";
    }
    else if (currentNode == myLinkedList)
    {
        std::cout << "Error: No element before the head!\n";
    }
    else if (beforeCurrentNode == myLinkedList)
    {
        linkedLists[name] = currentNode;
        std::cout << beforeCurrentNode->data << "\n";
        delete beforeCurrentNode;
    }
    else
    {
        beforeBefore->next = currentNode;
        std::cout << beforeCurrentNode->data << "\n";
        delete beforeCurrentNode;
    }
}

void fdelVal(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];
    if (isLLEmpty(myLinkedList))
        return;

    Node *currentNode = myLinkedList;
    Node *beforeCurrentNode = nullptr;

    while (currentNode != nullptr && currentNode->data != value)
    {
        beforeCurrentNode = currentNode;
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)
    {
        std::cout << "Error: Element not found!\n";
    }
    else
    {
        if (beforeCurrentNode == nullptr)
        {
            linkedLists[name] = myLinkedList->next;
        }
        else if (currentNode->next == nullptr)
        {
            beforeCurrentNode->next = nullptr;
        }
        else
        {
            beforeCurrentNode->next = currentNode->next;
        }

        std::cout << currentNode->data << "\n";
        delete currentNode;
    }
}

void fGet(std::stringstream &ss)
{
    std::string name;
    std::string value;
    int posCnt = 0;
    ss >> name >> value;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];
    if (isLLEmpty(myLinkedList))
        return;

    Node *currentNode = myLinkedList;

    while (currentNode != nullptr && currentNode->data != value)
    {
        currentNode = currentNode->next;
        posCnt++;
    }

    if (currentNode == nullptr)
    {
        std::cout << "Error: Element not found!\n";
    }
    else
    {
        std::cout << posCnt << "\n";
    }
}

void fPrint(std::stringstream &ss)
{
    std::string name;
    ss >> name;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];

    Node *currentNode = myLinkedList;
    while (currentNode != nullptr)
    {
        std::cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    std::cout << "\n";
}

void fgetBeg(std::stringstream &ss)
{
    std::string name;
    ss >> name;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];

    std::cout << myLinkedList->data << "\n";
}

void fgetEnd(std::stringstream &ss)
{
    std::string name;
    ss >> name;

    if (isLinkedListNamedInvalid(name))
        return;
    Node *myLinkedList = linkedLists[name];

    Node *currentNode = myLinkedList;
    while (currentNode->next != nullptr)
    {
        currentNode = currentNode->next;
    }
    std::cout << currentNode->data << "\n";
}