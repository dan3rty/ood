#pragma once

#include "../Coffee/CPortionedCoffee.h"

class CCappuccino final : public CPortionedCoffee
{
public:
    explicit CCappuccino(CoffeePortion portion = CoffeePortion::Standard);

    [[nodiscard]] double GetCost() const override;
};