#include "CLiqueur.h"

CLiqueur::CLiqueur(IBeveragePtr&& beverage, LiqueurType type)
    : CCondimentDecorator(std::move(beverage))
    , m_type(type)
{
}

std::string CLiqueur::GetCondimentDescription() const
{
    return GetTypeDescription() + " Liqueur";
}

double CLiqueur::GetCondimentCost() const
{
    return 50;
}

std::string CLiqueur::GetTypeDescription() const
{
    switch (m_type)
    {
        case LiqueurType::Nut:
            return "Nut";
        case LiqueurType::Chocolate:
            return "Chocolate";
        default:
            return {};
    }
}