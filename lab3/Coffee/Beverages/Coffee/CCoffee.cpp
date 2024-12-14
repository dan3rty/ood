#include "CCoffee.h"

CCoffee::CCoffee(std::string const& description)
    : CBeverage(description)
{
}

double CCoffee::GetCost() const
{
    return 60;
}