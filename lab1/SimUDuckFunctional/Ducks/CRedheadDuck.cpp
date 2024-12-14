#include "CRedheadDuck.h"

CRedheadDuck::CRedheadDuck()
    : CDuck(
        CreateQuackBehavior(),
        CreateFlyWithWingsBehavior(),
        CreateDanceMinuetBehavior())
{
}

void CRedheadDuck::Display() const
{
    std::cout << "I'm a redhead duck" << std::endl;
}