#pragma once

#include <chrono>
#include <iostream>

class Timer
{
public:
    Timer()
    {
        _start = std::chrono::high_resolution_clock::now();
    }
    ~Timer()
    {
        _end = std::chrono::high_resolution_clock::now();
        _duration = (_end - _start);

        std::cout << "Time elapsed: " << _duration.count() * 1000.0 << " ns" << std::endl;
    }

public:
    std::chrono::time_point<std::chrono::high_resolution_clock> _start, _end;
    std::chrono::duration<double> _duration;
};