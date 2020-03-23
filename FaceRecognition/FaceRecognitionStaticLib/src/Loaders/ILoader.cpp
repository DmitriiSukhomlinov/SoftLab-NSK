#include "ILoader.h"
#include "AviLoader.h"

ILoader* ILoader::createLoader() {
    return new AviLoader;
}