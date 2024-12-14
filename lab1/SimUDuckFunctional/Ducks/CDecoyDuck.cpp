#include "CDecoyDuck.h"

CDecoyDuck::CDecoyDuck()
    : CDuck(
        CreateMuteQuackBehavior(),
        CreateFlyNoWayBehavior(),
        CreateDanceNoWayBehavior())
{
}

void CDecoyDuck::Display() const
{
    std::cout << "I'm a decoy duck" << std::endl;
}