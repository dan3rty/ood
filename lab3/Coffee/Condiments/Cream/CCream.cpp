#include "CCream.h"

CCream::CCream(IBeveragePtr&& beverage)
    : CCondimentDecorator(std::move(beverage))
{
}

std::string CCream::GetCondimentDescription() const
{
    return "Cream";
}

double CCream::GetCondimentCost() const
{
    return 25;
}