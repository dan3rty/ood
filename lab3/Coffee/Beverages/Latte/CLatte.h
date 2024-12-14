#pragma once

#include "../Coffee/CPortionedCoffee.h"

class CLatte final : public CPortionedCoffee
{
public:
    explicit CLatte(CoffeePortion portion = CoffeePortion::Standard);

    [[nodiscard]] double GetCost() const override;
};