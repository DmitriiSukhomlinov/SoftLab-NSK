#include <iostream>
using namespace std;

#define CHECK(condition, messageOk, messageError, result) \
	if (condition) { \
		cout << messageOk << endl; \
	} else { \
		cout << messageError << endl; \
		system("pause"); \
		return result; \
	} \
