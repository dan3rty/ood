#include "CBeverage.h"

CBeverage::CBeverage(std::string const& description)
    : m_description(description)
{
}

std::string CBeverage::GetDescription() const
{
    return m_description;
}