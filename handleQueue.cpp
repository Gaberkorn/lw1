#include "handleQueue.h"

bool isQueueEmpty(Queue *&queue)
{
    if (queue == nullptr || queue->head == nullptr)
    {
        std::cout << "Error: Queue is empty!\n";
        return true;
    }
    return false;
}

bool isQueueNamedInvalid(const std::string &name)
{
    if (queues.find(name) == queues.end() || queues[name] == nullptr)
    {
        std::cout << "Error: Queue '" << name << "' doesn't exist!\n";
        return true;
    }
    return false;
}

void qpush(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;
    if (ss.fail())
        return;

    if (queues.find(name) == queues.end() || queues[name] == nullptr)
    {
        queues[name] = new Queue{nullptr, nullptr};
    }

    Queue *myQueue = queues[name];
    Node *newNode = new Node{value, nullptr};

    if (myQueue->head == nullptr)
    {
        myQueue->head = newNode;
    }
    else
    {
        myQueue->tail->next = newNode;
    }
    myQueue->tail = newNode;
    std::cout << value << "\n";
}
void qpop(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isQueueNamedInvalid(name))
        return;

    Queue *myQueue = queues[name];
    if (isQueueEmpty(myQueue))
        return;

    Node *deleteNode = myQueue->head;
    std::cout << deleteNode->data << "\n";

    if (myQueue->head == myQueue->tail)
    {
        myQueue->head = nullptr;
        myQueue->tail = nullptr;
    }
    else
    {
        myQueue->head = myQueue->head->next;
    }
    std::cout << deleteNode->data << "\n";
    delete deleteNode;
}
void qfront(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isQueueNamedInvalid(name))
        return;

    Queue *myQueue = queues[name];
    if (isQueueEmpty(myQueue))
        return;

    std::cout << myQueue->head->data << "\n";
}
void qprint(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isQueueNamedInvalid(name))
        return;

    Node *current = queues[name]->head;
    while (current != nullptr)
    {
        std::cout << current->data << " ";
        current = current->next;
    }
    std::cout << "\n";
}
