//Michal Urbanski
//Zeglowanie w czasie przyplywu
#include "Solution.h"

unsigned int Solution::Solve(unsigned int size, unsigned int* map)
{
	this->size = size;
	this->map = map;
	if(size == 1) return map[0];

	unsigned int low = 0; //highest not passable time found so far
	if(low < map[0]) low = map[0] - 1; // is the start tile
	if(low < map[size * size - 1]) low = map[size * size - 1] - 1; //or the end tile if bigger

	unsigned int high = 0; //lowest passable time found so far 
	unsigned int temp = 0; //temporary variable to find a value that can be passed

	while(high == 0) //double the value of low until high is set
	{
		temp = (1.5) * low + 1;	
		if(CheckTime(temp)) high = temp;
		else low = temp;
	}

	unsigned int time = (high + low)/2;
	while(high - low > 1)//narrow the lower and upper bound until the solution is found
	{
		if(CheckTime(time))
			high = time;
		else
			low = time;
		time = (high + low)/2;
	}
	return high;
}

bool Solution::CheckTime(unsigned int time)
{
	if(map[0] > time) return false;
	struct // 0 - DOWN, 1 - LEFT, 2 - UP, 3 - RIGHT
	{
		unsigned int direction;
		void TurnRight() { direction = (direction + 1)%4; }
		void TurnLeft() { direction = (direction + 3)%4; }
		int dx() { return direction%2 ? direction - 2 : 0; } //x coordinate of one step in this direction
		int dy() { return direction%2 ? 0 : 1 - direction; } //y coordinate of one step in this direction
	} dir; //temporary direction strucure to move on the map
	dir.direction = 0; //the direction is set to down
	int x = 0, y = 0;

	while( x!=0 || y!=0 || dir.direction!=2 ) //traversing the map until back to start facing up
	{
		if((unsigned int) x == size-1 &&
			(unsigned int) y == size-1) return true; //if found the end tile, returns true
		if(StepPossible(x + dir.dx(), y + dir.dy(), time)) //takes step if possible
		{
			x += dir.dx();
			y += dir.dy();
			dir.TurnRight();
			continue;
		}
		else dir.TurnLeft(); //else tries another direction
	}
	return false;
}

bool Solution::StepPossible(int x, int y, unsigned int time)
{
	if(x < 0 || y < 0) return false;
	if((unsigned int)x >= size || (unsigned int)y >= size) return false;
	if(map[(unsigned int)y * size + (unsigned int)x] > time) return false;
	return true;
}

void Swap(unsigned int& a, unsigned int& b)
{
	unsigned int swap = a;
	a = b;
	b = swap;
}