#pragma once

#include "../CCondimentDecorator.h"

enum class LiqueurType
{
    Nut,
    Chocolate,
};

class CLiqueur final : public CCondimentDecorator
{
public:
    explicit CLiqueur(IBeveragePtr&& beverage, LiqueurType type = LiqueurType::Nut);

protected:
    [[nodiscard]] std::string GetCondimentDescription() const override;
    [[nodiscard]] double GetCondimentCost() const override;

private:
    [[nodiscard]] std::string GetTypeDescription() const;

    LiqueurType m_type;
};