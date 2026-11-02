#ifndef ARRAYS_H
#define ARRAYS_H

#include <iostream>
#include <sstream>
#include <string>
#include <map>

struct Array
{
    Array(int value) {
        capacity = (value <= 0) ? 4 : value; // Защита: размер не может быть меньше 4
        size = 0;
        data = new std::string[capacity];
    }
    
    std::string *data = nullptr;
    int capacity = 0;
    int size = 0;

    void increaseSize()
    {
        std::string *biggerArray = new std::string[size * 2];

        for (int i = 0; i < size; i++)
        {
            biggerArray[i] = data[i];
        }

        delete[] data;
        data = biggerArray;
        capacity = size * 2;
    }
};

inline std::map<std::string, Array*> arrays;
bool isArrayNamedInvalid(const std::string& name);
void minit(std::stringstream &ss);
void mpush(std::stringstream &ss);
void minsert(std::stringstream &ss);
void mget(std::stringstream &ss);
void mdel(std::stringstream &ss);
void mreplace(std::stringstream &ss);
void mlen(std::stringstream &ss);
void mPrint(std::stringstream &ss);
#endif