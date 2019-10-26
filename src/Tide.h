#ifndef TIDE_H
#define TIDE_H

#include "Solution.h"
#include <string>

class Tide
{
    unsigned int size;
    unsigned int* map;
    bool dataCorrect;
    void ShellResolve(char choice);
    void LoadFromFile(std::string fileName = "data.txt");
    void LoadManually();
    void Allocate(unsigned int size);
    void Free();
    void Print();
    unsigned int Solve(unsigned int size, unsigned int* map);
    unsigned int Brute(unsigned int size, unsigned int* map);
    Solution problem;
public:
    void ShellLoop();
    Tide();
};

#endif
