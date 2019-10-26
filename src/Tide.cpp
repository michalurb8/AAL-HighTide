#include "Tide.h"
#include <fstream>
#include <iostream>

void Tide::LoadFromFile(std::string fileName)
{
	dataCorrect = true;
	std::ifstream input(fileName);

	if(input.eof()) 
	{
		dataCorrect = false;
		std::cout << "File Empty" << std::endl;
	}

	input >> size;
	Allocate(size);

	for(unsigned int i = 0; i < size * size; ++i)
	{
		input >> map[i];	
		if(input.eof())
		{
			dataCorrect = false;
			break;
		}
	}

	input.close();
	if(dataCorrect) std::cout << "Data loaded successfully" << std::endl;
	else std::cout << "Error loading data" << std::endl;
}

void Tide::LoadManually()
{
	dataCorrect = true;
	std::cin >> size;
	Allocate(size);
	for(unsigned int i = 0; i < size * size; ++i)
	{
		std::cin >> map[i];	
	}
}

void Tide::Allocate(unsigned int size)
{
	delete[] map;
	map = new unsigned int[size * size];
}

void Tide::Free()
{
	delete[] map;
	map = new unsigned int[1];
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

unsigned int Tide::Solve(unsigned int size, unsigned int* map)
{
	if(!dataCorrect)
	{
		std::cout << "Data not loaded, returning ";
		return 0;
	}
	return problem.Solve(size, map);
}

unsigned int Tide::Brute(unsigned int size, unsigned int* map)
{
	if(!dataCorrect)
	{
		std::cout << "Data not loaded, returning ";
		return 0;
	}
	return problem.Brute(size, map);
}

Tide::Tide()
{
	size = 1;
	map = new unsigned int[1];
	dataCorrect = false;
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
            "   1 - Load data from data.txt file" << std::endl <<
            "   2 - Load data from any .txt file" << std::endl <<
            "   3 - Load data manually" << std::endl << std::endl <<
            "   h - Display this help message" << std::endl <<
            "   p - Print loaded data" << std::endl <<
            "   r - Reset loaded data" << std::endl <<
            "   s - Solve and display" << std::endl <<
            "   b - Brute force solution" << std::endl <<
            "   q - Exit" << std::endl;
            return;
        case '1':
            LoadFromFile();
            return;
        case '2':
	    LoadFromFile("other.txt");
            return;
        case '3':
	    LoadManually();
            return;
        case 'p':
	    Print();
            return;
        case 'r':
	    Free();
            return;
        case 's':
	    std::cout << Solve(size, map) << std::endl;
            return;
        case 'b':
	    std::cout << Brute(size, map) << std::endl;
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
        choice =  temp[0];
        ShellResolve(choice);
    } while(choice != 'q');
}
