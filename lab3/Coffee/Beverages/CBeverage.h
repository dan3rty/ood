#pragma once

#include "IBeverage.h"

class CBeverage : public IBeverage
{
public:
    explicit CBeverage(std::string const& description);

    [[nodiscard]] std::string GetDescription() const override;

private:
    std::string m_description;
};