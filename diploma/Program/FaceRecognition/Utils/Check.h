#pragma once

#include <iostream>
using namespace std;

#define CHECK_IF_FALSE(condition, result) \
    if (!condition) { \
        return result; \
    } \

#define CHECK_IF_FALSE_RETURN(condition, messageOk, messageError, result) \
    if (condition) { \
        cout << messageOk << endl; \
    } else { \
        cout << messageError << endl; \
        system("pause"); \
        return result; \
    } \

#define CHECK_IF_FALSE_RETURN_NO_OK_MESSAGE(condition, messageError, result) \
    if (!condition) { \
        cout << messageError << endl; \
        return result; \
    } \

#define CHECK_IF_FALSE_PAUSE(condition, messageOk, messageError) \
    if (condition) { \
        cout << messageOk << endl; \
    } else { \
        cout << messageError << endl; \
        system("pause"); \
    } \

#define CHECK_IF_FALSE_CONTINUE(condition, messageError) \
    if (!condition) { \
        cout << messageError << endl; \
        continue; \
    } \

#define CHECK_IF_FALSE_CONTINUE_NO_MESSAGE(condition) \
    if (!condition) { \
        continue; \
    } \


#define CHECK_IF_FALSE_BREAK(condition) \
    if (!condition) { \
        break; \
    } \

