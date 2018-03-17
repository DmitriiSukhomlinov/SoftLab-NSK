#include <iostream>
using namespace std;

#define CHECK_RETURN(condition, messageOk, messageError, result) \
    if (condition) { \
        cout << messageOk << endl; \
    } else { \
        cout << messageError << endl; \
        system("pause"); \
        return result; \
    } \

#define CHECK_PAUSE(condition, messageOk, messageError) \
    if (condition) { \
        cout << messageOk << endl; \
    } else { \
        cout << messageError << endl; \
        system("pause"); \
    } \

