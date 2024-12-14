#pragma once

#include "../CCondimentDecorator.h"

enum class IceCubeType
{
    Dry,
    Water,
};

class CIceCubes final : public CCondimentDecorator
{
public:
    CIceCubes(IBeveragePtr&& beverage, unsigned quantity, IceCubeType type = IceCubeType::Water);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;

private:
    unsigned m_quantity;
    IceCubeType m_type;
};