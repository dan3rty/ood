#pragma once

#include <memory>
#include <string>

class IBeverage
{
public:
    [[nodiscard]] virtual std::string GetDescription() const = 0;
    [[nodiscard]] virtual double GetCost() const = 0;

    virtual ~IBeverage() = default;
};

using IBeveragePtr = std::unique_ptr<IBeverage>;