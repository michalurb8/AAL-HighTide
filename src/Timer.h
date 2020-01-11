//Michal Urbanski
//Zeglowanie w czasie przyplywu
#pragma once
#include <string>
#include <iostream>
#include <chrono>

class Timer
{
    bool running;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    void Stop();
public:
    Timer(std::string timerName);
    ~Timer();
};