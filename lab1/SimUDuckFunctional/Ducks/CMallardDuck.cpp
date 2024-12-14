#include "CMallardDuck.h"

CMallardDuck::CMallardDuck()
    : CDuck(
        CreateQuackBehavior(),
        CreateFlyWithWingsBehavior(),
        CreateDanceValseBehavior())
{
}

void CMallardDuck::Display() const
{
    std::cout << "I'm a mallard duck" << std::endl;
}