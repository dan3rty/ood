#include "CCinnamon.h"

CCinnamon::CCinnamon(IBeveragePtr&& beverage)
    : CCondimentDecorator(std::move(beverage))
{
}

std::string CCinnamon::GetCondimentDescription() const
{
    return "Cinnamon";
}

double CCinnamon::GetCondimentCost() const
{
    return 20;
}