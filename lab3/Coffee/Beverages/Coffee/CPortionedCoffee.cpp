#include "CPortionedCoffee.h"

CPortionedCoffee::CPortionedCoffee(const std::string& description, CoffeePortion portion)
    : CCoffee(description)
    , m_portion(portion)
{
}

std::string CPortionedCoffee::GetDescription() const
{
    return GetPortionDescription() + " " + CBeverage::GetDescription();
}

CoffeePortion CPortionedCoffee::GetPortion() const
{
    return m_portion;
}

std::string CPortionedCoffee::GetPortionDescription() const
{
    switch (m_portion)
    {
        case CoffeePortion::Standard:
            return "Standard";
        case CoffeePortion::Double:
            return "Double";
        default:
            return {};
    }
}