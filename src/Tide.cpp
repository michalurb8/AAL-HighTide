//Michal Urbanski
//Zeglowanie w czasie przyplywu
#include <fstream>
#include <iostream>
#include "Timer.h"
#include "Tide.h"

Tide::Tide()
{
	srand(time(NULL));
	size = 1;
	map = new unsigned int[1];
	dataCorrect = false;
}

Tide::~Tide()
{
	delete[] map;
}

bool Tide::LoadFromFile(std::string fileName)
{
	if(fileName == "")
	{
		std::cout << "Input file's name:" << std::endl;
		std::cin >> fileName;
	}
	dataCorrect = false;
	std::ifstream input(fileName);
	if(input.fail())
	{
		std::cout << "Such a file does not exist" << std::endl;
		return false;
	}
	input >> size;
	Reallocate(size);

	if(size == 0)
	{
			input.close();
			std::cout << "File error, map size cannot be zero" << std::endl;
			return false;
	}
	for(unsigned int i = 0; i < size * size; ++i)
	{
		input >> map[i];	
		if(input.eof())
		{
			input.close();
			std::cout << "File error, dimensions do not match" << std::endl;
			return false;
		}
	}
	input.close();
	dataCorrect = true;
	return true;
}

void Tide::LoadManually()
{
	size = GetInt("Input map's size, N:", MINSIZE, MAXSIZE);
	Reallocate(size);
	for(unsigned int i = 0; i < size * size; ++i)
	{
		map[i] = GetInt("Input next element in the map:", 0, MAXHEIGHT);
	}
	dataCorrect = true;
}

void Tide::Reallocate(unsigned int size)
{
	delete[] map;
	map = new unsigned int[size * size];
	dataCorrect = false;
}

void Tide::Print()
{
	if(!dataCorrect)
	{
		std::cout << "Please load data" << std::endl;
		return;
	}
	for(unsigned int i = 0; i < size; ++i)
	{
		for(unsigned int j = 0; j < size; ++j)
			std::cout << map[i * size + j] << " ";
		std::cout << std::endl;
	}
}

unsigned int Tide::Solve(unsigned int* map)
{
	if(!dataCorrect)
	{
		std::cout << "Data not loaded, returning ";
		return 0;
	}
	else if(size == 0)
	{
		std::cout << "Error, map size ";
		return 0;
	}
	return problem.Solve(size, map);
}

void Tide::Test(unsigned int iterations, unsigned int range, unsigned int minSize, unsigned int maxSize)
{
	if(iterations == 0 || range == 0 || minSize == 0 || maxSize == 0)
	{
		iterations = GetInt("Input the number of iterations:", 1, MAXITER);
		range = GetInt("Input the range of the map height values:", 0, MAXHEIGHT);
		minSize = GetInt("Input the minimal size of the map:", MINSIZE, MAXSIZE);
		maxSize = GetInt("Input the maximal size of the map:", MINSIZE, MAXSIZE);
		if(minSize > maxSize) std::cout << "Warning: minimal size is greater than maximal, returning." << std::endl;
	}
	std::ofstream output("results.txt");
	output << "size range iterations time" << std::endl;
	std::cout << "Iterations: " << iterations << std::endl;
	std::cout << "Range: " << range << std::endl;
	for(unsigned int newSize = minSize; newSize < maxSize; newSize*=2)
	{
		std::cout << "Now checking size: " << newSize << std::endl;
		output << newSize << " " << range << " " << iterations << " ";
		output << SolveN(iterations, newSize, range)/iterations << std::endl;
	}
	output.close();
}

float Tide::SolveN(unsigned int iterations, unsigned int newSize, unsigned int range)
{
	if(iterations == 0 || newSize == 0 || range == 0)
	{
		iterations = GetInt("Input the number of iterations:", 1, MAXITER);
		range = GetInt("Input the range of the map height values:", 0, MAXHEIGHT);
		newSize = GetInt("Input the size of the map:", MINSIZE, MAXSIZE);
	}
	float time = 0;
	for(unsigned int i = 0; i < iterations; ++i)
	{
		Generate(newSize, range);
		LoadFromFile("default.txt");
		{
			Timer timer("Solve in a loop");
			Solve(map);
			float temp = timer.Stop();
			time += temp;
		}
	}
	return time/iterations;
}

unsigned int Tide::GetInt(std::string prompt, unsigned int min, unsigned int max)
{
	unsigned int temp = 0;
	bool isCorrect = false;
	prompt += " (min: " + std::to_string(min) + ", max: " + std::to_string(max) + ")";
	while(!isCorrect)
	{
		std::cout << prompt << std::endl;
		std::cin >> temp;
		if(std::cin.fail())
		{
			std::cout << "Error, not an integer" << std::endl;
			std::cin.clear();
			std::cin.ignore();
		}
		else if(temp > max)
			std::cout << "Error, integer too large, max is: " << max << std::endl;
		else if(temp < min)
			std::cout << "Error, integer too small, min is: " << min << std::endl;
		else isCorrect = true;
	}
	return temp;
}

void Tide::Generate(unsigned int size, unsigned int range)
{
	if(size == 0 || range == 0)
	{
		size = GetInt("Input the size of the map:", MINSIZE, MAXSIZE);
		range = GetInt("Input the range of the map height values:", 0, MAXHEIGHT);
	}
	unsigned int* buffer = new unsigned int[size * size];
	for(unsigned int i = 0; i < size*size; ++i)
	{
		buffer[i] = rand()%range;
	}
	std::ofstream output("default.txt");
	output << size << std::endl;
	for(unsigned int i = 0; i < size; ++i)
	{
		for(unsigned int j = 0; j < size; ++j)
		{
			output << buffer[i * size + j] << " ";
		}
		output << std::endl;
	}
	output.close();
	delete[] buffer;
}

void Tide::ShellResolve(char choice)
{
	float temp = 0;
    switch(choice)
    {
	case 'q':
		std::cout << "Shutting down..." << std::endl << std::endl;
		return;
        case 'h':
            std::cout << std::endl <<
            "Available commands:" << std::endl << std::endl <<
            "   x - Load data from default.txt file" << std::endl <<
            "   y - Load data from any .txt file" << std::endl <<
            "   z - Load data manually" << std::endl <<
            "   p - Print loaded data" << std::endl << std::endl << 
            "   g - Generate random data to default.txt" << std::endl <<
            "   s - Solve and display" << std::endl <<
            "   l - Solve in a loop, show the time" << std::endl << std::endl <<
            "   d - Perform the default size test, results in results.txt" << std::endl <<
            "   c - Perform a custom test, results in results.txt" << std::endl << std::endl << 
            "   h - Display this help message" << std::endl <<
            "   q - Exit" << std::endl;
			return;
		case 'x':
			if(LoadFromFile("default.txt"))
				std::cout << "Data loaded successfully" << std::endl;
			return;
		case 'y':
	    	if(LoadFromFile(""))
				std::cout << "Data loaded successfully" << std::endl;
            return;
        case 'z':
	    	LoadManually();
			std::cout << "Data loaded successfully" << std::endl;
            return;
        case 'p':
	    	Print();
            return;
		case 'g':
			Generate();
			std::cout << "Data generated successfully" << std::endl;
			return;
		case 's':
	    	std::cout << "Solution: " << Solve(map) << std::endl;
            return;
		case 'l':
			temp = SolveN();
			std::cout << "It took " << temp << "s on average" << std::endl;
			return;
        case 'd':
	    	Test(10, 1000000000, 8, 5000);
			std::cout << "Results in results.txt" << std::endl;
            return;
        case 'c':
	    	Test();
			std::cout << "Results in results.txt" << std::endl;
            return;
        default:
            std::cout << "Unknown command. Try 'h' for help." << std::endl;
    }
}

void Tide::ShellLoop()
{
    char choice;
    ShellResolve('h');
    do
    {
        std::string temp;
        std::cout << std::endl << "> ";
        std::cin >> temp;
		if(temp.length() > 1)
			choice = 0;
		else
        	choice =  temp[0];
        ShellResolve(choice);
    } while(choice != 'q');
}