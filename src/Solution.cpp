#include "Solution.h"
#include <iostream>
#include <chrono>

unsigned int Solution::Brute(unsigned int size, unsigned int* map)
{
	this->size = size;
	this->map = map;
	unsigned int time = map[0];
	if(map[0] < map[size * size -1]) time = map[size * size - 1];
	while(1)
	{
		if(CheckTime(time)) return time;
		++time;
	}
	return -1;
}
//DUPA WYWWALIC SOLVE, DAC TYLKO BRUTE ZMIENIONY I DODAC INNY BRUTE >:CCCCCCC
unsigned int Solution::Solve(unsigned int size, unsigned int* map)
{
	this->size = size;
	this->map = map;
	unsigned int* buf = new unsigned int[size * size - 1];
	for(unsigned int i = 0; i < size * size - 1; ++i)
	{
		buf[i] = map[i];
	}
	unsigned int low; //first index in ordered map
	low = 0;
	unsigned int high; //end index in ordered map
	high = size * size - 1;  

	unsigned int current = high/2; //set current to the current position in sorted map
	unsigned int time = GetNth(buf, 0, size * size - 1, current);//set time to the median of the whole map

	while(high - low > 1)
	{
		if(CheckTime(time))
			high = current;
		else
			low = current;
		current = (high + low)/2;
		time = GetNth(buf, 0, size * size - 1, current);
	}
	current = buf[high];
	return current;
}

bool Solution::CheckTime(unsigned int time)
{
	if(map[0] > time) return false;
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
unsigned int Solution::GetNth(unsigned int* buf, unsigned int beg, unsigned int end, unsigned int index)
{
    if(beg >= end) return buf[index];
	if(beg + 1 == end)
	{
		if(buf[beg] > buf[end]) Swap(buf[beg], buf[end]);
		return buf[index];
	}

	if(buf[(beg + end)/2] > buf[end]) Swap(buf[(beg + end)/2], buf[end]);
	if(buf[beg] > buf[(beg + end)/2]) Swap(buf[beg], buf[(beg + end)/2]); //Setting pivot to median of three
	if(buf[(beg + end)/2] < buf[end]) Swap(buf[(beg + end)/2], buf[end]); // Moving pivot to the end

	unsigned int firstbig = beg; //firstbig is the index of the first element bigger than the pivot (so far)
	for(unsigned int i = beg; i < end; ++i)
	{
		if(buf[i] <= buf[end])
		{
			Swap(buf[i], buf[firstbig]);
			++firstbig;
		}
	}
    
	Swap(buf[firstbig], buf[end]); //inserting pivot back to its place, to index firstbig

    if(firstbig == index) return buf[index];
	if(firstbig < index) return GetNth(buf, firstbig + 1, end, index);
	else return GetNth(buf, beg, firstbig - 1, index);
}