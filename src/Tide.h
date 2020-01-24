//Michal Urbanski
//Zeglowanie w czasie przyplywu
#pragma once

#include "Solution.h"
#include <string>

class Tide
{
    unsigned int size;
    unsigned int* map;

	const unsigned int MINSIZE = 1;
	const unsigned int MAXSIZE = 10000;
	const unsigned int MAXHEIGHT = 1000000000;
	const unsigned int MAXITER = 1000;

    bool dataCorrect;
    void ShellResolve(char choice);
    unsigned int GetInt(std::string prompt, unsigned int min, unsigned int max);

    bool LoadFromFile(std::string fileName = "data.txt");
    void LoadManually();

    void Reallocate(unsigned int size);

    void Print();
    void Generate(unsigned int size = 0, unsigned int range = 0);
    unsigned int Solve(unsigned int* map);
    void Test(unsigned int iter = 0, unsigned int range = 0, unsigned int minSize = 0, unsigned int maxSize = 0);
    float SolveN(unsigned int iterations = 0, unsigned int newSize = 0, unsigned int range = 0);
    Solution problem;
public:
    void ShellLoop();
    Tide();
    ~Tide();
};