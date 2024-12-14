#include "DanceBehaviors.h"

DanceBehavior CreateDanceMinuetBehavior()
{
    return []() {
        std::cout << "I'm dancing minuet!!!" << std::endl;
    };
}

DanceBehavior CreateDanceValseBehavior()
{
    return []() {
        std::cout << "I'm dancing valse!!!" << std::endl;
    };
}

DanceBehavior CreateDanceNoWayBehavior()
{
    return []() {};
}
