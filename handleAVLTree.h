#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <sstream>
#include <string>
#include <queue>
#include <map>

struct TreeNode
{
    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}

    int data;
    TreeNode *left;
    TreeNode *right;
};

class AVLTree
{
private:
    void inOrderTreeWalk(TreeNode *currentNode)
    {
        if (currentNode == nullptr)
        {
            std::cout << "# ";
            return;
        }
        inOrderTreeWalk(currentNode->left);
        std::cout << currentNode->data << " ";
        inOrderTreeWalk(currentNode->right);
    }

    void preOrderTreeWalk(TreeNode *currentNode)
    {
        if (currentNode == nullptr)
        {
            std::cout << "# ";
            return;
        }
        std::cout << currentNode->data << " ";
        preOrderTreeWalk(currentNode->left);
        preOrderTreeWalk(currentNode->right);
    }

    void postOrderTreeWalk(TreeNode *currentNode)
    {
        if (currentNode == nullptr)
        {
            std::cout << "# ";
            return;
        }
        postOrderTreeWalk(currentNode->left);
        postOrderTreeWalk(currentNode->right);
        std::cout << currentNode->data << " ";
    }

    void BFS(TreeNode *currentNode)
    {
        std::queue<TreeNode *> myQueue;

        myQueue.push(root);

        while (!myQueue.empty())
        {
            std::string currentLevel;
            int queueSize = myQueue.size();

            for (int i = 0; i < queueSize; i++)
            {
                TreeNode *currentNode = myQueue.front();
                currentLevel = currentLevel + std::to_string(currentNode->data) + " ";

                if (currentNode->left != nullptr)
                    myQueue.push(currentNode->left);
                if (currentNode->right != nullptr)
                    myQueue.push(currentNode->right);
                myQueue.pop();
            }
            std::cout << currentLevel << "\n";
        }
    }

    bool searchValue(int value, TreeNode *current)
    {
        if (current == nullptr)
            return false;
        else if (value == current->data)
            return true;
        else if (value < current->data)
            return searchValue(value, current->left);
        else
            return searchValue(value, current->right);
    }

    int height(TreeNode *node)
    {
        if (node == nullptr)
            return -1;
        else
        {
            int lheight = height(node->left);
            int rhieght = height(node->right);
            if (lheight > rhieght)
                return lheight + 1;
            else
                return rhieght + 1;
        }
    }

    int getBalanceFactor(TreeNode *currentNode)
    {
        if (currentNode == nullptr)
            return -1;
        else
            return height(currentNode->left) - height(currentNode->right);
    }

    TreeNode *leftRotate(TreeNode *x)
    {
        TreeNode *y = x->right;
        TreeNode *T2 = y->left;

        y->left = x;
        x->right = T2;
        return y;
    }

    TreeNode *rightRotate(TreeNode *y)
    {
        TreeNode *x = y->left;
        TreeNode *T2 = x->right;

        x->right = y;
        y->left = T2;
        return x;
    }

    TreeNode *minValueNode(TreeNode *node)
    {
        TreeNode *currentNode = node;
        while (currentNode->left != nullptr)
            currentNode = currentNode->left;
        return currentNode;
    }

    TreeNode *insertNode(TreeNode *node, int &value)
    {
        if (node == nullptr)
        {
            return new TreeNode{value};
        }

        if (value < node->data)
        {
            node->left = insertNode(node->left, value);
        }
        else if (value > node->data)
        {
            node->right = insertNode(node->right, value);
        }
        else
            return node;

        int bf = getBalanceFactor(node);

        if (bf > 1 && value < node->left->data)
            return rightRotate(node);
        if (bf < -1 && value > node->right->data)
            return leftRotate(node);
        if (bf > 1 && value > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (bf < -1 && value < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    TreeNode *deleteNode(TreeNode *node, int value)
    {
        if (node == nullptr)
            return node;
        else if (value < node->data)
            node->left = deleteNode(node->left, value);
        else if (value > node->data)
            node->right = deleteNode(node->right, value);
        else
        {
            if (node->left == nullptr)
            {
                TreeNode *temp = node->right;
                node->right = nullptr;
                delete node;
                return temp;
            }
            else if (node->right == nullptr)
            {
                TreeNode *temp = node->left;
                delete node;
                return temp;
            }
            else
            {
                TreeNode *temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = deleteNode(node->right, temp->data);
            }
        }

        int bf = getBalanceFactor(node);

        if (bf == 2 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);
        else if (bf == 2 && getBalanceFactor(node->left) == -1)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        else if (bf == -2 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);
        else if (bf == -2 && getBalanceFactor(node->right) == 1)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void writeTreeToStr(TreeNode *currentNode, std::string &filestream)
    {
        if (currentNode == nullptr)
        {
            filestream = filestream + "# ";
            return;
        }

        filestream = filestream + std::to_string(currentNode->data) + " ";
        writeTreeToStr(currentNode->left, filestream);
        writeTreeToStr(currentNode->right, filestream);
    }

    TreeNode *readTreeFromStr(std::stringstream &ss)
    {
        std::string token;
        if (!(ss >> token) || token == "#")
        {
            return nullptr;
        }

        int value = std::stoi(token);
        TreeNode *node = new TreeNode(value);

        node->left = readTreeFromStr(ss);

        node->right = readTreeFromStr(ss);

        return node;
    }


    TreeNode *root;

public:
    AVLTree() { root = nullptr; }

    bool find(int value)
    {
        return searchValue(value, root);
    }

    void insert(int value)
    {
        root = insertNode(root, value);
    }

    void deleteVal(int value)
    {
        root = deleteNode(root, value);
    }

    void inOrderPrint()
    {
        if (root == nullptr)
            std::cout << "\n";
        else
        {
            inOrderTreeWalk(root);
            std::cout << "\n";
        }
    }

    void preOrderPrint()
    {
        if (root == nullptr)
            std::cout << "\n";
        else
        {
            preOrderTreeWalk(root);
            std::cout << "\n";
        }
    }

    void postOrderPrint()
    {
        if (root == nullptr)
            std::cout << "\n";
        else
        {
            postOrderTreeWalk(root);
            std::cout << "\n";
        }
    }

    void BFSprint()
    {
        if (root == nullptr)
            std::cout << "\n";
        else
        {
            BFS(root);
        }
    }

    bool chkIfRootEmpty()
    {
        if (root == nullptr)
            return true;
        else
            return false;
    }

    bool write(std::string &filestream)
    {
        if (root == nullptr)
        {
            return false;
        }
        else
        {
            writeTreeToStr(root, filestream);
            return true;
        }
    }

    void read(std::stringstream &ss)
    {
        root = readTreeFromStr(ss);
    }
};

inline std::map<std::string, AVLTree*> avlTrees;

bool isTreeNamedInvalid(const std::string &name);
void executeAVLTreeCommand(const std::string &command, std::stringstream &ss);

#endif