//Michal Urbanski
//Zeglowanie w czasie przyplywu
#pragma once

#include "Solution.h"
#include <string>

class Tide
{
    unsigned int size;
    unsigned int* map;

	const unsigned int maxsize = 10000;
	const unsigned int maxheight = 1000000000;
	const unsigned int maxiter = 1000;

    bool dataCorrect;
    void ShellResolve(char choice);
    unsigned int GetInt(std::string prompt, unsigned int max);

    void LoadFromFile(std::string fileName = "data.txt");
    void LoadManually();

    void Allocate(unsigned int size);

    void Print();
    void Generate(unsigned int size = 0, unsigned int range = 0);
    unsigned int Solve(unsigned int* map, bool runOptimal);
    void LogN(bool runOptimal);
    Solution problem;
public:
    void ShellLoop();
    Tide();
    ~Tide();
};