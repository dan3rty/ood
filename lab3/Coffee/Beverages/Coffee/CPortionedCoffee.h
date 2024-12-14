#pragma once

#include "CCoffee.h"

enum class CoffeePortion
{
    Standard,
    Double,
};

class CPortionedCoffee : public CCoffee
{
public:
    explicit CPortionedCoffee(std::string const& description, CoffeePortion portion = CoffeePortion::Standard);

    [[nodiscard]] std::string GetDescription() const override;

protected:
    [[nodiscard]] CoffeePortion GetPortion() const;

private:
    [[nodiscard]] std::string GetPortionDescription() const;

    CoffeePortion m_portion;
};