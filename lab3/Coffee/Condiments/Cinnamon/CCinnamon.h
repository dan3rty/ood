#pragma once

#include "../CCondimentDecorator.h"

class CCinnamon final : public CCondimentDecorator
{
public:
    explicit CCinnamon(IBeveragePtr&& beverage);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;
};