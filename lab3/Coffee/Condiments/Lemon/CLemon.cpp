#include "CLemon.h"

CLemon::CLemon(IBeveragePtr&& beverage, unsigned quantity)
    : CCondimentDecorator(std::move(beverage))
    , m_quantity(quantity)
{
}

std::string CLemon::GetCondimentDescription() const
{
    return "Lemon x " + std::to_string(m_quantity);
}

double CLemon::GetCondimentCost() const
{
    return 10 * m_quantity;
}