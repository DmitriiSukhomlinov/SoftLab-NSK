#include "IAviLoader.h"
#include "AviLoader.h"

ILoader* ILoader::createLoader() {
    return new AviLoader;
}