#include "CRubberDuck.h"

CRubberDuck::CRubberDuck()
    : CDuck(
        CreateSqueakBehavior(),
        CreateFlyNoWayBehavior(),
        CreateDanceNoWayBehavior())
{
}

void CRubberDuck::Display() const
{
    std::cout << "I'm a rubber duck" << std::endl;
}