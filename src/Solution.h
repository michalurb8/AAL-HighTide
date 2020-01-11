//Michal Urbanski
//Zeglowanie w czasie przyplywu
#pragma once

class Solution
{
	unsigned int size;
	unsigned int* map;
	bool CheckTime(unsigned int time);
	bool StepPossible(int x, int y , unsigned int time);
public:
	unsigned int Solve(unsigned int size, unsigned int* map);
	unsigned int Brute(unsigned int size, unsigned int* map);
};