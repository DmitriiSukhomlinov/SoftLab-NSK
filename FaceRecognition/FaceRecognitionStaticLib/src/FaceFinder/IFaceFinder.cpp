#include "IFaceFinder.h"
#include "FaceFinder.h"

IFaceFinder* IFaceFinder::createFaceFinder() {
    return new FaceFinder;
}