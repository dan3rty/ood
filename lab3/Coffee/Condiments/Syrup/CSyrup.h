#pragma once

#include "../CCondimentDecorator.h"

enum class SyrupType
{
    Chocolate,
    Maple,
};

class CSyrup final : public CCondimentDecorator
{
public:
    explicit CSyrup(IBeveragePtr&& beverage, SyrupType syrupType = SyrupType::Chocolate);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;

private:
    SyrupType m_syrupType;
};