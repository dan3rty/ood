#include "FlyBehaviors.h"
#include <iostream>

FlyBehavior CreateFlyWithWingsBehavior()
{
    return [flightCount = 0]() mutable -> int {
        ++flightCount;
        std::cout << "I'm flying with wings for "
                  << flightCount << " time"
                  << " and counting!!" << std::endl;
        return flightCount;
    };
}

FlyBehavior CreateFlyNoWayBehavior()
{
    return {};
}