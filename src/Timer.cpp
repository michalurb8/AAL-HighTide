//Michal Urbanski
//Zeglowanie w czasie przyplywu
#include "Timer.h"

Timer::Timer(std::string timerName)
{
    start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer()
{
    if(running) Stop();
}

void Timer::Stop()
{
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    std::cout << "It took " << duration.count()*1000 << "ms " << std::endl;
}