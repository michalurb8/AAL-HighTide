#ifndef TIDE_H
#define TIDE_H

#include "Solution.h"
#include <string>

class Tide
{
    unsigned int size;
    unsigned int* map;

	const unsigned int maxsize = 10000;
	const unsigned int maxheight = 1000000000;

    bool dataCorrect;
    void ShellResolve(char choice);
    unsigned int GetInt(std::string prompt, unsigned int max);

    void LoadFromFile(std::string fileName = "data.txt");
    void LoadManually();

    void Allocate(unsigned int size);

    void Print();
    void Generate();
    unsigned int Solve(unsigned int size, unsigned int* map, bool runOptimal);
    Solution problem;
public:
    void ShellLoop();
    Tide();
    ~Tide();
};

#endif
