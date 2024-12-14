#include "CMilkshake.h"

CMilkshake::CMilkshake(MilkshakePortion portion)
    : CBeverage("Milkshake")
    , m_portion(portion)
{
}

std::string CMilkshake::GetDescription() const
{
    return GetPortionDescription() + " " + CBeverage::GetDescription();
}

double CMilkshake::GetCost() const
{
    switch (m_portion)
    {
        case MilkshakePortion::Small:
            return 50;
        case MilkshakePortion::Standard:
            return 60;
        case MilkshakePortion::Grand:
            return 80;
        default:
            return 0;
    }
}

std::string CMilkshake::GetPortionDescription() const
{
    switch (m_portion)
    {
        case MilkshakePortion::Small:
            return "Small";
        case MilkshakePortion::Standard:
            return "Standard";
        case MilkshakePortion::Grand:
            return "Grand";
        default:
            return {};
    }
}