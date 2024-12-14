#include "CCondimentDecorator.h"

CCondimentDecorator::CCondimentDecorator(IBeveragePtr&& beverage)
    : m_beverage(std::move(beverage))
{
}

std::string CCondimentDecorator::GetDescription() const
{
    return m_beverage->GetDescription() + ", " + GetCondimentDescription();
}

double CCondimentDecorator::GetCost() const
{
    return m_beverage->GetCost() + GetCondimentCost();
}