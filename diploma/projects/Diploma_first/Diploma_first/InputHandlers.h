#pragma once
#include <string>
using namespace std;

class InputHandlers {
public:
    static const bool inputBool(string valueDefinition);
    static const int inputInt(string valueDefinition);

private:
    static const string TRUE;
    static const string FALSE;
    static const int ERROR_VALUE;
};