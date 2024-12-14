#include "CChocolateCrumbs.h"

CChocolateCrumbs::CChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass)
    : CCondimentDecorator(std::move(beverage))
    , m_mass(mass)
{
}

std::string CChocolateCrumbs::GetCondimentDescription() const
{
    return "Chocolate crumbs " + std::to_string(m_mass) + "g";
}

double CChocolateCrumbs::GetCondimentCost() const
{
    return 2 * m_mass;
}