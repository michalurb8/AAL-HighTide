#include "Tide.h"
#include <fstream>
#include <iostream>

Tide::Tide()
{
	size = 1;
	map = new unsigned int[1];
	dataCorrect = false;
}

Tide::~Tide()
{
	delete[] map;
}

void Tide::LoadFromFile(std::string fileName)
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
		std::cout << "Such a file does not exist." << std::endl;
		return;
	}

	input >> size;
	Allocate(size);

	if(size == 0)
	{
			input.close();
			std::cout << "Error loading data" << std::endl;
			return;
	}
	for(unsigned int i = 0; i < size * size; ++i)
	{
		input >> map[i];	
		if(input.eof())
		{
			input.close();
			std::cout << "Error loading data" << std::endl;
			return;
		}
	}

	input.close();
	dataCorrect = true;
	std::cout << "Data loaded successfully" << std::endl;
}

void Tide::LoadManually()
{
	dataCorrect = true;
	size = GetInt("Input map's size, N:", maxsize);
	Allocate(size);
	for(unsigned int i = 0; i < size * size; ++i)
	{
		map[i] = GetInt("Input next element in the map:", maxheight);
	}
}

void Tide::Allocate(unsigned int size)
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

unsigned int Tide::Solve(unsigned int size, unsigned int* map, bool runOptimal)
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
	if(runOptimal)
		return problem.Solve(size, map);
	else
		return problem.Brute(size, map);
}

unsigned int Tide::GetInt(std::string prompt, unsigned int max)
{
	unsigned int temp = 0;
	bool isCorrect = false;
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
			std::cout << "Error, integer too big" << std::endl;
		else isCorrect = true;
	}
	return temp;
}

void Tide::Generate()
{
	srand(time(NULL));
	rand(); rand(); rand(); rand();

	unsigned int size = 0, range = 0;
	size = GetInt("Input the size of the map:", maxsize);
	range = GetInt("Input the range of the map height values:", maxheight);

	std::ofstream output("default.txt");
	output << size << std::endl;
	unsigned int* buffer = new unsigned int[size * size];
	for(unsigned int i = 0; i < size*size; ++i)
	{
		buffer[i] = rand()%range;
	}
	for(unsigned int i = 0; i < size; ++i)
	{
		for(unsigned int j = 0; j < size; ++j)
		{
			output << buffer[i * size + j] << " ";
		}
		output << std::endl;
	}
	delete[] buffer;
	output.close();
}

void Tide::ShellResolve(char choice)
{
    switch(choice)
    {
	case 'q':
		std::cout << "Shutting down..." << std::endl << std::endl;
		return;
        case 'h':
            std::cout << std::endl <<
            "Available commands:" << std::endl << std::endl <<
            "   1 - Load data from default.txt file" << std::endl <<
            "   2 - Load data from any .txt file" << std::endl <<
            "   3 - Load data manually" << std::endl << std::endl <<
            "   h - Display this help message" << std::endl <<
            "   p - Print loaded data" << std::endl <<
            "   s - Solve and display" << std::endl <<
            "   b - Brute force solution" << std::endl <<
            "   g - Generate random data to example.txt" << std::endl <<
            "   q - Exit" << std::endl;
			return;
		case '1':
			LoadFromFile("default.txt");
			return;
		case '2':
	    	LoadFromFile("");
            return;
        case '3':
	    	LoadManually();
            return;
        case 'p':
	    	Print();
            return;
		case 'g':
			Generate();
			return;
		case 's':
	    	std::cout << Solve(size, map, true) << std::endl;
            return;
		case 'b':
	    	std::cout << Solve(size, map, false) << std::endl;
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