#include "Solution.h"
#include <iostream>

unsigned int Solution::Brute(unsigned int size, unsigned int* map)
{
	this->size = size;
	this->map = map;
	unsigned int high = 0, low = -1, time;
	for(unsigned int i = 0; i < size * size; ++i)
	{
		if(map[i] > high) high = map[i];
		if(map[i] < low) low = map[i];
	}
	if(high == low) return high;
	for(time = low; time <= high; ++time)
	{
		if(CheckTime(time)) return time;
	}
	return -1;
}


unsigned int Solution::Solve(unsigned int size, unsigned int* map)
{
	this->size = size;
	this->map = map;
	unsigned int* buf = new unsigned int[size*size];
	for(unsigned int i = 0; i < size*size; ++i)
		buf[i] = map[i];
	for(unsigned int i = 0; i < size; ++i)
	{
		for(unsigned int j = 0; j < size; ++j)
			std::cout << map[i * size + j] << " ";
		std::cout << std::endl;
	}
	QuickSort(buf, 0, size*size);
	for(unsigned int i = 0; i < size; ++i)
	{
		for(unsigned int j = 0; j < size; ++j)
			std::cout << map[i * size + j] << " ";
		std::cout << std::endl;
	}

	unsigned int high = size * size - 1, low = 0;
	if(buf[high] == buf[low])
	{
		high = buf[0];
		delete[] buf;
		return high;
	}
	unsigned int index = (high + low)/2, time = buf[index];
	while(high - low > 1)
	{
		bool passable = false;
		passable = CheckTime(time);
		if(passable)
			high = index;
		else
			low = index;
		index = (high + low)/2;
		time = buf[index];
	}
	
	index = buf[high];
	delete[] buf;
	return index;
}

bool Solution::CheckTime(unsigned int time)
{

	struct // 0 - DOWN, 1 - LEFT, 2 - UP, 3 - RIGHT
	{
		unsigned int direction;
		void TurnRight() { direction = (direction + 1)%4; }
		void TurnLeft() { direction = (direction + 3)%4; }
		int dx() { return direction%2 ? direction - 2 : 0; }
		int dy() { return direction%2 ? 0 : 1 - direction; }
	} dir;
	dir.direction = 0;
	int x = 0, y = 0;

	while( x!=0 || y!=0 || dir.direction!=2 )
	{
		if((unsigned int) x == size-1 &&
			(unsigned int) y == size-1) return true;
		if(StepPossible(x + dir.dx(), y + dir.dy(), time))
		{
			x += dir.dx();
			y += dir.dy();
			dir.TurnRight();
			continue;
		}
		else dir.TurnLeft();
	}
	return false;
}

bool Solution::StepPossible(int x, int y, unsigned int time)
{
	typedef unsigned int UINT;
	if(x < 0 || y < 0) return false;
	if((UINT)x >= size || (UINT)y >= size) return false;
	if(map[(UINT)y * size + (UINT)x] > time) return false;
	return true;
}

void Swap(unsigned int& a, unsigned int& b)
{
	unsigned int swap = a;
	a = b;
	b = swap;
}

void Solution::QuickSort(unsigned int* buf, unsigned int beg, unsigned int end)
{//first element is the pivot
	if(beg == end) return;
	std::cout << "XD";
	unsigned int firstbig = beg + 1;
	for(unsigned int i = beg + 1; i <= end; ++i)
	{
		if(buf[i] < buf[beg])
		{
			Swap(buf[i], buf[firstbig]);
			++firstbig;
		}
	}
	Swap(buf[beg], buf[firstbig - 1]);
	QuickSort(buf, beg, firstbig - 1);
	QuickSort(buf, firstbig, end);
}
