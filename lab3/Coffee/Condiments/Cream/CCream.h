#pragma once

#include "../CCondimentDecorator.h"

class CCream final : public CCondimentDecorator
{
public:
    explicit CCream(IBeveragePtr&& beverage);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;
};