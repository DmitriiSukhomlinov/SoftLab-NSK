#include "LuxandFaceSDK.h"

#include "Consts.cpp"
#include "Macros.cpp"

int main() {
	int result = FSDK_ActivateLibrary(key); 
	CHECK(result == FSDKE_OK, "Correct key", "Activation error", 0);


	system("pause");
	return 0;
}