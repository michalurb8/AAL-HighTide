#ifndef SOLUTION_H
#define SOLUTION_H

class Solution
{
	unsigned int size;
	unsigned int* map;
	unsigned int GetNth(unsigned int* buf, unsigned int beg, unsigned int end, unsigned int index);
	bool CheckTime(unsigned int time);
	bool StepPossible(int x, int y , unsigned int time);
public:
	unsigned int Solve(unsigned int size, unsigned int* map);
	unsigned int Brute(unsigned int size, unsigned int* map);
};

#endif
