#include "CChocolateSlices.h"

CChocolateSlices::CChocolateSlices(IBeveragePtr&& beverage, unsigned quantity)
    : CCondimentDecorator(std::move(beverage))
    , m_quantity(quantity)
{
    if (m_quantity > MAX_SLICES)
    {
        throw std::invalid_argument("too many slices");
    }
}

std::string CChocolateSlices::GetCondimentDescription() const
{
    return "Chocolate slices x " + std::to_string(m_quantity);
}

double CChocolateSlices::GetCondimentCost() const
{
    return 10 * m_quantity;
}