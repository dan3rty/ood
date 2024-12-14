#include "CTea.h"

CTea::CTea(const TeaType type)
    : CBeverage("Tea")
    , m_type(type)
{
}

std::string CTea::GetDescription() const
{
    return GetTypeDescription() + " " + CBeverage::GetDescription();
}

double CTea::GetCost() const
{
    return 30;
}

std::string CTea::GetTypeDescription() const
{
    switch (m_type)
    {
        case TeaType::Black:
            return "Black";
        case TeaType::Oolong:
            return "Oolong";
        case TeaType::Karkade:
            return "Karkade";
        case TeaType::Green:
            return "Green";
        default:
            return {};
    }
}