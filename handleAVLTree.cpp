#include "handleAVLTree.h"

bool isTreeNamedInvalid(const std::string &name)
{
    if (avlTrees.find(name) == avlTrees.end() || avlTrees[name] == nullptr)
    {
        std::cout << "Error: Tree '" << name << "' doesn't exist!\n";
        return true;
    }
    return false;
}

void executeAVLTreeCommand(const std::string &command, std::stringstream &ss)
{
    if (command == "TINSERT")
    {
        std::string name;
        int value;
        ss >> name >> value;
        if (ss.fail()) return;

        if (avlTrees.find(name) == avlTrees.end() || avlTrees[name] == nullptr) {
            avlTrees[name] = new AVLTree();
        }

        avlTrees[name]->insert(value);
    }
    else if (command == "TDEL")
    {
        std::string name;
        int value;
        ss >> name >> value;
        if (ss.fail()) return;

        if (isTreeNamedInvalid(name)) return;
        avlTrees[name]->deleteVal(value);
    }
    else if (command == "TSEARCH")
    {
        std::string name;
        int value;
        ss >> name >> value;
        if (ss.fail()) return;

        if (isTreeNamedInvalid(name)) return;
        if (avlTrees[name]->find(value))
            std::cout << "Value '" << value << "' found.\n";
        else
            std::cout << "Value '" << value << "' not found.\n";
    }
    else if (command == "TPRINT_INORDER")
    {
        std::string name;
        ss >> name;
        if (isTreeNamedInvalid(name)) return;
        avlTrees[name]->inOrderPrint();
    }
    else if (command == "TPRINT_PREORDER")
    {
        std::string name;
        ss >> name;
        if (isTreeNamedInvalid(name)) return;
        avlTrees[name]->preOrderPrint();
    }
    else if (command == "TPRINT_POSTORDER")
    {
        std::string name;
        ss >> name;
        if (isTreeNamedInvalid(name)) return;
        avlTrees[name]->postOrderPrint();
    }
    else if (command == "TPRINT_BFS")
    {
        std::string name;
        ss >> name;
        if (isTreeNamedInvalid(name)) return;
        avlTrees[name]->BFSprint();
    }
}
