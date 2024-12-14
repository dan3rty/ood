#pragma once

#include "../CCondimentDecorator.h"

class CChocolateSlices final : public CCondimentDecorator
{
public:
    CChocolateSlices(IBeveragePtr&& beverage, unsigned quantity);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;

private:
    static constexpr unsigned MAX_SLICES = 5;

    unsigned m_quantity;
};