#include "InputHandlers.h"

#include <iostream>

const string InputHandlers::TRUE = "true";
const string InputHandlers::FALSE = "false";
const int InputHandlers::ERROR_VALUE = -10000;

const bool InputHandlers::inputBool(string valueDefinition) {
    cout << valueDefinition << endl << "Print 'true' or 'false'" << endl;
    string value;
    cin >> value;
    while (value != TRUE && value != FALSE) {
        cout << "Incorrect value, please enter again:" << endl;
        cin.clear();
        cin >> value;
    }

    bool result = false;
    if (value == TRUE) {
        result = true;
    }
    return result;
}

const int InputHandlers::inputInt(string valueDefinition) {
    cout << valueDefinition << endl << "Print the number" << endl;
    int value = ERROR_VALUE;
    cin >> value;
    while (value == ERROR_VALUE) {
        cout << "Incorrect value, please enter again:" << endl;
        cin.clear();
        cin >> value;
    }

    return value;
}

