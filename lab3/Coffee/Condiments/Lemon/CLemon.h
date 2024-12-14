#pragma once

#include "../CCondimentDecorator.h"

class CLemon final : public CCondimentDecorator
{
public:
    explicit CLemon(IBeveragePtr&& beverage, unsigned quantity = 1);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;

private:
    unsigned m_quantity;
};