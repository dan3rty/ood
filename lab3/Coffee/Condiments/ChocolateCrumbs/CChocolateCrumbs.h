#pragma once

#include "../CCondimentDecorator.h"

class CChocolateCrumbs final : public CCondimentDecorator
{
public:
    CChocolateCrumbs(IBeveragePtr&& beverage, unsigned mass);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;

private:
    unsigned m_mass;
};