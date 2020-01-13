//Michal Urbanski
//Zeglowanie w czasie przyplywu
#pragma once
#include <string>
#include <iostream>
#include <chrono>

class Timer
{
    bool running;
    std::string name;
    std::chrono::time_point<std::chrono::system_clock> start, end;
public:
    Timer(std::string timerName);
    ~Timer();
    float Stop();
};