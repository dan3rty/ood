#pragma once

#include "IStyle.h"

class IOutlineStyle : public IStyle
{
public:
	[[nodiscard]] virtual std::optional<double> GetThickness() const = 0;
	virtual void SetThickness(double thickness) = 0;
};
