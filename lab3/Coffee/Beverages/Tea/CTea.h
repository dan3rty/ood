#pragma once

#include "../CBeverage.h"

enum class TeaType
{
    Black,
    Green,
    Oolong,
    Karkade,
};

class CTea final : public CBeverage
{
public:
    explicit CTea(TeaType type = TeaType::Black);

    [[nodiscard]] std::string GetDescription() const override;
    [[nodiscard]] double GetCost() const override;

private:
    [[nodiscard]] std::string GetTypeDescription() const;

    TeaType m_type;
};