#include "handleDoubleLinkedList.h"

bool isDLLEmpty(DLL *&ll)
{
    if (ll == nullptr || ll->head == nullptr)
    {
        std::cout << "Error: Linked list is empty!\n";
        return true;
    }
    else
        return false;
}

bool isDLLNamedInvalid(const std::string &name)
{
    if (dLinkedLists.find(name) == dLinkedLists.end() || dLinkedLists[name] == nullptr)
    {
        std::cout << "Error: Double Linked list '" << name << "' doesn't exist!\n";
        return true;
    }
    return false;
}

void laddBeg(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;
    if (ss.fail())
        return;

    if (dLinkedLists.find(name) == dLinkedLists.end() || dLinkedLists[name] == nullptr)
    {
        dLinkedLists[name] = new DLL{nullptr, nullptr};
    }

    DLL *myList = dLinkedLists[name];
    DLL_Node *newNode = new DLL_Node{value, myList->head, nullptr};

    if (myList->head == nullptr)
    {
        myList->head = newNode;
        myList->tail = newNode;
    }
    else
    {
        myList->head->back = newNode;
        myList->head = newNode;
    }
    std::cout << value << "\n";
}
void laddEnd(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;
    if (ss.fail())
        return;

    if (dLinkedLists.find(name) == dLinkedLists.end() || dLinkedLists[name] == nullptr)
    {
        dLinkedLists[name] = new DLL{nullptr, nullptr};
    }

    DLL *myList = dLinkedLists[name];
    DLL_Node *newNode = new DLL_Node{value, nullptr, myList->tail};

    if (myList->head == nullptr)
    {
        myList->head = newNode;
        myList->tail = newNode;
    }
    else
    {
        myList->tail->next = newNode;
        myList->tail = newNode;
    }
    std::cout << value << "\n";
}
void laddAfter(std::stringstream &ss)
{
    std::string name;
    std::string value;
    std::string newData;
    ss >> name >> value >> newData;
    if (ss.fail())
        return;

    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];
    if (isDLLEmpty(myList))
        return;

    DLL_Node *currentNode = myList->head;
    while (currentNode != nullptr && currentNode->data != value)
    {
        currentNode = currentNode->next;
    }

    if (currentNode != nullptr)
    {
        DLL_Node *newNode = new DLL_Node{newData, currentNode->next, currentNode};
        if (currentNode->next != nullptr)
        {
            newNode->next->back = newNode;
        }
        else
        {
            myList->tail = newNode;
        }
        currentNode->next = newNode;
    }
    else
    {
        std::cout << "Error: Element not found!\n";
    }
    std::cout << newData << "\n";
}
void laddBefore(std::stringstream &ss)
{
    std::string name;
    std::string value;
    std::string newData;
    ss >> name >> value >> newData;
    if (ss.fail())
        return;

    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];
    if (isDLLEmpty(myList))
        return;

    DLL_Node *currentNode = myList->head;
    while (currentNode != nullptr && currentNode->data != value)
    {
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)
    {
        std::cout << "Error: Element not found!\n";
    }
    else if (currentNode == myList->head)
    {
        DLL_Node *newNode = new DLL_Node{newData, myList->head, nullptr};
        myList->head->back = newNode;
        myList->head = newNode;
    }
    else
    {
        DLL_Node *newNode = new DLL_Node{newData, currentNode, currentNode->back};
        currentNode->back->next = newNode;
        currentNode->back = newNode;
    }
    std::cout << newData << "\n";
}
void ldelBeg(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];
    if (isDLLEmpty(myList))
        return;

    DLL_Node *deleteNode = myList->head;
    myList->head = myList->head->next;
    if (myList->head == nullptr)
    {
        myList->tail = nullptr;
    }
    else
    {
        myList->head->back = nullptr;
    }
    std::cout << deleteNode->data << "\n";
    delete deleteNode;
}
void ldelEnd(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];
    if (isDLLEmpty(myList))
        return;

    DLL_Node *deleteNode = myList->tail;
    myList->tail = myList->tail->back;
    if (myList->tail == nullptr)
    {
        myList->head = nullptr;
    }
    else
    {
        myList->tail->next = nullptr;
    }
    std::cout << deleteNode->data << "\n";
    delete deleteNode;
}
void ldelAfter(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;
    if (ss.fail())
        return;

    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];
    if (isDLLEmpty(myList))
        return;

    DLL_Node *currentNode = myList->head;
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
        std::cout << "Error: No element after it!!\n";
    }
    else
    {
        DLL_Node *deleteNode = currentNode->next;
        currentNode->next = deleteNode->next;
        if (deleteNode->next != nullptr)
        {
            deleteNode->next->back = currentNode;
        }
        else
        {
            myList->tail = currentNode;
        }
        std::cout << deleteNode->data << "\n";
        delete deleteNode;
    }
}
void ldelBefore(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;
    if (ss.fail())
        return;

    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];
    if (isDLLEmpty(myList))
        return;

    DLL_Node *currentNode = myList->head;
    while (currentNode != nullptr && currentNode->data != value)
    {
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)
    {
        std::cout << "Error: Element not found!\n";
    }
    else if (currentNode == myList->head)
    {
        std::cout << "Error: No element before the head!\n";
    }
    else if (currentNode->back == myList->head)
    {
        DLL_Node *deleteNode = myList->head;
        myList->head = myList->head->next;
        myList->head->back = nullptr;
        std::cout << deleteNode->data << "\n";
        delete deleteNode;
    }
    else
    {
        DLL_Node *deleteNode = currentNode->back;
        deleteNode->back->next = currentNode;
        currentNode->back = deleteNode->back;
        std::cout << deleteNode->data << "\n";
        delete deleteNode;
    }
}
void ldelVal(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;
    if (ss.fail())
        return;

    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];
    if (isDLLEmpty(myList))
        return;

    DLL_Node *currentNode = myList->head;
    while (currentNode != nullptr && currentNode->data != value)
    {
        currentNode = currentNode->next;
    }

    if (currentNode == nullptr)
    {
        std::cout << "Error: Element not found!\n";
    }
    else
    {
        if (currentNode->back != nullptr)
        {
            currentNode->back->next = currentNode->next;
        }
        else
        {
            myList->head = currentNode->next;
        }

        if (currentNode->next != nullptr)
        {
            currentNode->next->back = currentNode->back;
        }
        else
        {
            myList->tail = currentNode->back;
        }
        std::cout << currentNode->data << "\n";
        delete currentNode;
    }
}
void lGet(std::stringstream &ss)
{
    std::string name;
    std::string value;
    int posCnt = 0;
    ss >> name >> value;
    if (ss.fail())
        return;

    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];
    if (isDLLEmpty(myList))
        return;

    DLL_Node *currentNode = myList->head;
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
void lPrint(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isDLLNamedInvalid(name))
        return;
    DLL *myList = dLinkedLists[name];

    DLL_Node *currentNode = myList->head;
    while (currentNode != nullptr)
    {
        std::cout << currentNode->data << " ";
        currentNode = currentNode->next;
    }
    std::cout << "\n";
}
void lgetBeg(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isDLLNamedInvalid(name))
        return;
    std::cout << dLinkedLists[name]->head->data << "\n";
}
void lgetEnd(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isDLLNamedInvalid(name))
        return;
    std::cout << dLinkedLists[name]->tail->data << "\n";
}