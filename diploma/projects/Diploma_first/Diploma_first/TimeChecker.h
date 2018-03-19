#pragma once

#include <chrono>
#include <string>

using namespace std;
using namespace std::chrono;

class TimeChecker
{
public:
    TimeChecker();

    enum ChronoType {
        Nanoseconds,
        Microseconds,
        Milliseconds,
        Seconds
    };

    //Start point of the measurement
    void startTimer(string _actionName);
    //Finish point. The function prints time since start in milliseconds
    void checkTimer(ChronoType type);

private:
    template <typename T>
    long long defineTime();

    steady_clock::time_point start;
    string actionName;
    bool wasStarted;
};

