#include "TimeChecker.h"

#include <iostream>

TimeChecker::TimeChecker() : start(steady_clock::now()), wasStarted(false) {}

void TimeChecker::startTimer(string _actionName) {
    start = steady_clock::now();
    actionName = _actionName;
    wasStarted = true;
}

void TimeChecker::checkTimer(ChronoType type) {
    if (!wasStarted) {
        cout << "Timer error! Timer was not setted" << endl;
        return;
    }

    const auto finish = steady_clock::now();
    auto elapsed = start.time_since_epoch();
    string timeType;
    switch (type) {//Smt wrong with microseconds
    case Nanoseconds:
        elapsed = duration_cast<nanoseconds>(finish - start);
        timeType = " nanoseconds";
        break;
    case Microseconds:
        elapsed = duration_cast<microseconds>(finish - start);
        timeType = " microseconds";
        break;
    case Milliseconds:
        elapsed = duration_cast<milliseconds>(finish - start);
        timeType = " milliseconds";
        break;
    case Seconds:
        elapsed = duration_cast<seconds>(finish - start);
        timeType = " seconds";
        break;
    }
    cout << "Time for the '" << actionName << "' operation = " 
         << elapsed.count() << timeType << endl;

    actionName.clear();
    wasStarted = false;
}

