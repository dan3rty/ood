#include "CModelDuck.h"

CModelDuck::CModelDuck()
    : CDuck(
        CreateQuackBehavior(),
        CreateFlyNoWayBehavior(),
        CreateDanceNoWayBehavior())
{
}

void CModelDuck::Display() const
{
    std::cout << "I'm a model duck" << std::endl;
}