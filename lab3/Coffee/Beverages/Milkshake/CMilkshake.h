#pragma once

#include "../CBeverage.h"

enum class MilkshakePortion
{
    Small,
    Standard,
    Grand,
};

class  CMilkshake final : public CBeverage
{
public:
    explicit CMilkshake(MilkshakePortion portion = MilkshakePortion::Standard);

    [[nodiscard]] std::string GetDescription() const override;
    [[nodiscard]] double GetCost() const override;

private:
    [[nodiscard]] std::string GetPortionDescription() const;

    MilkshakePortion m_portion;
};