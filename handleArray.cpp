#include "handleArray.h"

bool isArrayNamedInvalid(const std::string &name)
{
    if (arrays.find(name) == arrays.end() || arrays[name] == nullptr)
    {
        std::cout << "Error: Array '" << name << "' doesn't exist!\n";
        return true;
    }
    return false;
}

void minit(std::stringstream &ss)
{
    std::string name;
    int size;
    ss >> name >> size;

    if (ss.fail() || size <= 0 || name.empty())
    {
        std::cout << "Error: Invalid command format! Usage: MINIT <name> <size>\n";
        return;
    }
    if (arrays.find(name) != arrays.end())
    {
        std::cout << "Error: Array '" << name << "' already exists!\n";
        return;
    }

    arrays[name] = new Array(size);
    std::cout << size << "\n";
}
void mpush(std::stringstream &ss)
{
    std::string name;
    std::string value;
    ss >> name >> value;

    if (isArrayNamedInvalid(name) || ss.fail())
        return;

    Array *myArray = arrays[name];
    if (myArray->size == myArray->capacity)
    {
        myArray->increaseSize();
    }

    myArray->data[myArray->size] = value;
    myArray->size++;
    std::cout << value << "\n";
}

void minsert(std::stringstream &ss)
{
    std::string name;
    int index;
    std::string value;
    ss >> name >> index >> value;

    if (isArrayNamedInvalid(name) || ss.fail())
        return;

    Array *myArray = arrays[name];
    if (index < 0 || index > myArray->size)
    {
        std::cout << "Error: Index is out of bounds!\n";
        return;
    }

    if ((myArray->size == myArray->capacity))
        myArray->increaseSize();

    std::string *tempArray = new std::string[myArray->capacity];

    tempArray[index] = value;

    for (int i = 0; i < index; i++)
    {
        tempArray[i] = myArray->data[i];
    }

    for (int i = index; i < myArray->size; i++)
    {
        tempArray[i + 1] = myArray->data[i];
    }

    delete[] myArray->data;
    myArray->data = tempArray;
    myArray->size++;

    std::cout << value << "\n";
}

void mget(std::stringstream &ss)
{
    std::string name;
    int index;
    ss >> name >> index;

    if (isArrayNamedInvalid(name) || ss.fail())
        return;

    Array *myArray = arrays[name];
    if (index < 0 || index >= myArray->size)
    {
        std::cout << "Error: Index is out of bounds!\n";
        return;
    }

    std::cout << myArray->data[index] << "\n";
}

void mdel(std::stringstream &ss)
{
    std::string name;
    int index;
    ss >> name >> index;

    if (isArrayNamedInvalid(name) || ss.fail())
        return;

    Array *myArray = arrays[name];
    if (index < 0 || index >= myArray->size)
    {
        std::cout << "Error: Index is out of bounds!\n";
        return;
    }

    std::string *tempArray = new std::string[myArray->capacity];

    for (int i = 0; i < index; i++)
    {
        tempArray[i] = myArray->data[i];
    }

    for (int i = index + 1; i < myArray->size; i++)
    {
        tempArray[i - 1] = myArray->data[i];
    }

    delete[] myArray->data;
    myArray->data = tempArray;
    myArray->size = myArray->size - 1;
    std::cout << index << "\n";
}

void mreplace(std::stringstream &ss)
{
    std::string name;
    int index;
    std::string value;
    ss >> name >> index >> value;

    if (isArrayNamedInvalid(name) || ss.fail())
        return;

    Array *myArray = arrays[name];
    if (index < 0 || index >= myArray->size)
    {
        std::cout << "Error: Index is out of bounds!\n";
        return;
    }

    myArray->data[index] = value;
    std::cout << value << "\n";
}

void mlen(std::stringstream &ss)
{
    std::string name;
    ss >> name;

    if (isArrayNamedInvalid(name) || ss.fail())
        return;

    Array *myArray = arrays[name];
    std::cout << "Current array's size: " << myArray->size
              << ".\nArray's capacity: " << myArray->capacity << ".\n";
}

void mPrint(std::stringstream &ss)
{
    std::string name;
    ss >> name;
    if (isArrayNamedInvalid(name) || ss.fail())
        return;

    Array *myArray = arrays[name];
    for (int i = 0; i < myArray->size; i++)
    {
        std::cout << myArray->data[i] << " ";
    }
    std::cout << std::endl;
}