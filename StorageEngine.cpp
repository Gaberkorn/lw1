#include "StorageEngine.h"

void loadFromFile(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
            continue;

        std::stringstream ss(line);
        std::string header;
        ss >> header; // Считывается тег вроде [ARRAY:myarray]

        // Проверяется корректность формата тега
        if (header.front() != '[' || header.back() != ']')
            continue;

        // Убираются квадратные скобки
        std::string cleanHeader = header.substr(1, header.size() - 2);

        // Разделяется тип и имя по двоеточию
        size_t colonPos = cleanHeader.find(':');
        if (colonPos == std::string::npos)
            continue;

        std::string type = cleanHeader.substr(0, colonPos);
        std::string name = cleanHeader.substr(colonPos + 1);

        if (type == "ARRAY")
        {
            std::string inputData;
            std::string emptySlot = "#";
            std::vector<std::string> tokens;

            while (ss >> inputData)
            {
                tokens.push_back(inputData);
            }

            int requiredCapacity = tokens.size();
            if (requiredCapacity == 0)
                continue;

            Array *myArray = new Array(requiredCapacity);

            for (const auto &token : tokens)
            {
                if (token == emptySlot)
                {
                    break;
                }

                myArray->data[myArray->size] = token;
                myArray->size++;
            }

            arrays[name] = myArray;
        }

        else if (type == "LINKEDLIST")
        {
            std::string currentData;
            Node *myLinkedList = nullptr;

            while (ss >> currentData)
            {
                Node *newNode = new Node{currentData, nullptr};
                if (myLinkedList == nullptr)
                    myLinkedList = newNode;
                else
                {
                    Node *currentNode = myLinkedList;
                    while (currentNode->next != nullptr)
                    {
                        currentNode = currentNode->next;
                    }

                    currentNode->next = newNode;
                }
                linkedLists[name] = myLinkedList;
            }
        }

        else if (type == "DOUBLELINKEDLIST")
        {
            std::string currentData;
            DLL *myDLL = new DLL{nullptr, nullptr};

            while (ss >> currentData)
            {
                DLL_Node *newNode = new DLL_Node{currentData, nullptr, myDLL->tail};

                if (myDLL->head == nullptr)
                {
                    myDLL->head = newNode;
                    myDLL->tail = newNode;
                }
                else
                {
                    myDLL->tail->next = newNode;
                    myDLL->tail = newNode;
                }
            }
            dLinkedLists[name] = myDLL;
        }

        else if (type == "STACK")
        {
            std::string currentData;
            Stack *myStack = new Stack{nullptr};
            Node *tempHead = nullptr;

            while (ss >> currentData)
            {
                int val = std::stoi(currentData);
                Node *newNode = new Node{currentData, tempHead};
                tempHead = newNode;
            }

            while (tempHead != nullptr)
            {
                Node *popNode = tempHead;
                tempHead = tempHead->next;

                popNode->next = myStack->head;
                myStack->head = popNode;
            }
            stacks[name] = myStack;
        }

        else if (type == "QUEUE")
        {
            std::string currentData;
            Queue *myQueue = new Queue{nullptr, nullptr};

            while (ss >> currentData)
            {
                Node *newNode = new Node{currentData, nullptr};

                if (myQueue->head == nullptr)
                {
                    myQueue->head = newNode;
                }
                else
                {
                    myQueue->tail->next = newNode;
                }
                myQueue->tail = newNode;
            }
            queues[name] = myQueue;
        }

        else if (type == "AVLTREE")
        {
            AVLTree *myTree = new AVLTree();
            myTree->read(ss);
            avlTrees[name] = myTree;
        }
    }

    file.close();
}

void saveToFile(const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
        return;

    for (auto const &[name, arr] : arrays)
    {
        file << "[ARRAY:" << name << "] ";
        for (int i = 0; i < arr->size; i++)
        {
            file << arr->data[i] << " ";
        }
        for (int i = 0; i < (arr->capacity - arr->size); i++)
        {
            file << "# ";
        }
        file << "\n";
    }

    for (auto const &[name, ll] : linkedLists)
    {
        if (ll == nullptr)
            continue;
        file << "[LINKEDLIST:" << name << "] ";

        Node *currentNode = ll;
        while (currentNode != nullptr)
        {
            file << currentNode->data << " ";
            currentNode = currentNode->next;
        }
        file << "\n";
    }

    for (auto const &[name, dll] : dLinkedLists)
    {
        if (dll == nullptr || dll->head == nullptr)
            continue;
        file << "[DOUBLELINKEDLIST:" << name << "] ";

        DLL_Node *currentNode = dll->head;
        while (currentNode != nullptr)
        {
            file << currentNode->data << " ";
            currentNode = currentNode->next;
        }
        file << "\n";
    }

    for (auto const &[name, st] : stacks)
    {
        if (st == nullptr || st->head == nullptr)
            continue;
        file << "[STACK:" << name << "] ";

        Node *current = st->head;
        while (current != nullptr)
        {
            file << current->data << " ";
            current = current->next;
        }
        file << "\n";
    }

    for (auto const &[name, q] : queues)
    {
        if (q == nullptr || q->head == nullptr)
            continue;
        file << "[QUEUE:" << name << "] ";

        Node *current = q->head;
        while (current != nullptr)
        {
            file << current->data << " ";
            current = current->next;
        }
        file << "\n";
    }

    for (auto const &[name, tree] : avlTrees)
    {
        if (tree == nullptr || tree->chkIfRootEmpty())
            continue;

        file << "[AVLTREE:" << name << "] ";
        std::string treeData = "";
        tree->write(treeData);
        file << treeData << "\n";
    }

    file.close();
}

void executeLinkedListCommand(const std::string &command, std::stringstream &ss)
{
    if (command == "FADD_BEG")
    {
        faddBeg(ss);
    }

    else if (command == "FADD_END")
    {
        faddEnd(ss);
    }

    else if (command == "FADD_AFTER")
    {
        faddAfter(ss);
    }

    else if (command == "FADD_BEFORE")
    {
        faddBefore(ss);
    }

    else if (command == "FDEL_BEG")
    {
        fdelBeg(ss);
    }

    else if (command == "FDEL_END")
    {
        fdelEnd(ss);
    }

    else if (command == "FDEL_AFTER")
    {
        fdelAfter(ss);
    }

    else if (command == "FDEL_BEFORE")
    {
        fdelBefore(ss);
    }

    else if (command == "FDEL_VAL")
    {
        fdelVal(ss);
    }

    else if (command == "FGET")
    {
        fGet(ss);
    }

    else if (command == "FPRINT")
    {
        fPrint(ss);
    }

    else if (command == "FGET_BEG")
    {
        fGet(ss);
    }

    if (command == "FGET_END")
    {
        fgetEnd(ss);
    }
}

void executeDLinkedListCommand(const std::string &command, std::stringstream &ss)
{
    if (command == "LADD_BEG")
    {
        laddBeg(ss);
    }

    else if (command == "LADD_END")
    {
        laddEnd(ss);
    }

    else if (command == "LADD_AFTER")
    {
        laddAfter(ss);
    }

    else if (command == "LADD_BEFORE")
    {
        laddBefore(ss);
    }

    else if (command == "LDEL_BEG")
    {
        ldelBeg(ss);
    }

    else if (command == "LDEL_END")
    {
        ldelEnd(ss);
    }

    else if (command == "LDEL_AFTER")
    {
        ldelAfter(ss);
    }

    else if (command == "LDEL_BEFORE")
    {
        ldelBefore(ss);
    }

    else if (command == "LDEL_VAL")
    {
        ldelVal(ss);
    }

    else if (command == "LGET")
    {
        lGet(ss);
    }

    else if (command == "LPRINT")
    {
        lPrint(ss);
    }

    else if (command == "LGET_BEG")
    {
        lGet(ss);
    }

    if (command == "LGET_END")
    {
        lgetEnd(ss);
    }
}

void executeArrayCommand(const std::string &command, std::stringstream &ss)
{
    if (command == "MINIT")
    {
        minit(ss);
    }
    else if (command == "MPUSH")
    {
        mpush(ss);
    }

    else if (command == "MINSERT")
    {
        minsert(ss);
    }

    else if (command == "MGET")
    {
        mget(ss);
    }

    else if (command == "MDEL")
    {
        mdel(ss);
    }

    else if (command == "MREPLACE")
    {
        mreplace(ss);
    }

    else if (command == "MLENGTH")
    {
        mlen(ss);
    }

    else if (command == "MPRINT")
    {
        mPrint(ss);
    }
}

void executeStackCommand(const std::string &command, std::stringstream &ss)
{
    if (command == "SPUSH")
    {
        spush(ss);
    }
    else if (command == "SPOP")
    {
        spop(ss);
    }
    else if (command == "STOP")
    {
        stop(ss);
    }
    else if (command == "SPRINT")
    {
        sprint(ss);
    }
}

void executeQueueCommand(const std::string &command, std::stringstream &ss)
{
    if (command == "QPUSH")
    {
        qpush(ss);
    }
    else if (command == "QPOP")
    {
        qpop(ss);
    }
    else if (command == "QFRONT")
    {
        qfront(ss);
    }
    else if (command == "QPRINT")
    {
        qprint(ss);
    }
}
