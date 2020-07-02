#include "TimeChecker.h"

#include <cassert>
#include <iostream>

TimeChecker::TimeChecker() : start(steady_clock::now()), wasStarted(false) {}

template <typename T>
long long TimeChecker::defineTime() {
    const auto finish = steady_clock::now();
    const auto elapsed = duration_cast<T>(finish - start);
    return elapsed.count();
}

void TimeChecker::startTimer(string _actionName) {
    start = steady_clock::now();
    actionName = _actionName;
    wasStarted = true;
}

long long TimeChecker::checkTimer(ChronoType type) {
    if (!wasStarted) {
        assert(false);
        system("pause");
        return 0;
    }

    long long time = -1;
    string timeType;
    switch (type) {
    case Nanoseconds:
        time = defineTime<nanoseconds>();
        timeType = " nanoseconds";
        break;
    case Microseconds:
        time = defineTime<microseconds>();
        timeType = " microseconds";
        break;
    case Milliseconds:
        time = defineTime<milliseconds>();
        timeType = " milliseconds";
        break;
    case Seconds:
        time = defineTime<seconds>();
        timeType = " seconds";
        break;
    default:
        assert(false);
        break;
    }
    cout << "Time for the '" << actionName << "' operation = " 
         << time << timeType << endl;

    actionName.clear();
    wasStarted = false;
    return time;
}

