#include "handleStack.h"

bool isStackEmpty(Stack *&stack)
{
    if (stack == nullptr || stack->head == nullptr)
    {
        std::cout << "Error: Stack is empty!\n";
        return true;
    }
    return false;
}

bool isStackNamedInvalid(const std::string &name)
{
    if (stacks.find(name) == stacks.end() || stacks[name] == nullptr)
    {
        std::cout << "Error: Stack '" << name << "' doesn't exist!\n";
        return true;
    }
    return false;
}

void spush(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;
    if (ss.fail())
        return;

    if (stacks.find(name) == stacks.end() || stacks[name] == nullptr)
    {
        stacks[name] = new Stack{nullptr};
    }

    Stack *myStack = stacks[name];
    Node *newNode = new Node{value, myStack->head};
    myStack->head = newNode;
    std::cout << value << "\n";
}
void spop(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isStackNamedInvalid(name))
        return;

    Stack *myStack = stacks[name];
    if (isStackEmpty(myStack))
        return;

    Node *newHead = myStack->head->next;
    std::cout << myStack->head->data << "\n";
    delete myStack->head;
    myStack->head = newHead;
}
void stop(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isStackNamedInvalid(name))
        return;

    Stack *myStack = stacks[name];
    if (isStackEmpty(myStack))
        return;

    std::cout << myStack->head->data << "\n";
}
void sprint(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isStackNamedInvalid(name))
        return;

    Node *current = stacks[name]->head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}
