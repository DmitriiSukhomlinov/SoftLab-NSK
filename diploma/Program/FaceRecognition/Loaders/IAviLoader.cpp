#include "IAviLoader.h"
#include "AviLoader.h"

IAviLoader* IAviLoader::createAviLoader() {
    return new AviLoader;
}