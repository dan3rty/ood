#pragma once

#include "../CCondimentDecorator.h"

class CCoconutFlakes final : public CCondimentDecorator
{
public:
    CCoconutFlakes(IBeveragePtr&& beverage, unsigned mass);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;

private:
    unsigned m_mass;
};