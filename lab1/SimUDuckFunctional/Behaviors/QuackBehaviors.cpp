#include "QuackBehaviors.h"

QuackBehavior CreateQuackBehavior()
{
    return []() {
        std::cout << "Quack Quack!!!" << std::endl;
    };
}

QuackBehavior CreateSqueakBehavior()
{
    return []() {
        std::cout << "Squeak!" << std::endl;
    };
}

QuackBehavior CreateMuteQuackBehavior()
{
    return []() {};
}