//Michal Urbanski
//Zeglowanie w czasie przyplywu
#include "Timer.h"

Timer::Timer(std::string timerName)
{
    start = std::chrono::high_resolution_clock::now();
    name = timerName;
}

Timer::~Timer()
{
    if(running)
    {
        std::cout << "Timer '" << name << "' stops." << std::endl;
        std::cout << "It took " << Stop() << "ms " << std::endl;
    }
}

float Timer::Stop()
{
    running = false;
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> duration = end - start;
    return duration.count();
}