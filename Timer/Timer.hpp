#pragma once

#include <chrono>
#include <iostream>
#include <thread>

class Timer
{
public:
    Timer()
    {
        _start = std::chrono::steady_clock::now();
    }
    ~Timer()
    {
        _end = std::chrono::steady_clock::now();
        _duration = std::chrono::duration_cast<std::chrono::microseconds>(_end - _start);

        std::cout << "Time elapsed: " << _duration.count() << " ns" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

public:
    std::chrono::time_point<std::chrono::steady_clock> _start, _end;
    std::chrono::duration<double, std::micro> _duration;
};