#ifndef SHELL_H
#define SHELL_H

#include "Shell.h"

void Shell::Loop()
{
    Resolve('h');
    do
    {
        std::string temp;
        std::cout << "> ";
        std::cin >> temp;
        choice =  temp[0];
        Resolve(choice);
    } while(choice != 'q');
}


void Shell::Resolve(char choice)
{
    switch(choice)
    {
        case 'h':
            std::cout << std::endl <<
            "Available commands:" << std::endl << std::endl <<
            "   1 - Take input from data.txt file" << std::endl <<
            "   2 - Take input from any .txt file" << std::endl <<
            "   3 - Input data by hand" << std::endl <<
            "   h - Display this help message" << std::endl <<
            "   q - Exit" << std::endl << std::endl;
            break;
        case '1':
            //data.txt
            break;
        case '2':
            //*.txt
            break;
        case '3':
            //manual
            break;
        default:
            std::cout << "Unknown command. Try 'h' for help." << std::endl;
    }
}

#endif