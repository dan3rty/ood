#pragma once

#include "../Shapes/CShape.h"

class IShapeFactory
{
public:
	// почему он не константный (или может его надо константным)
	virtual CShapePtr CreateShape(std::string const& description) = 0;

	virtual ~IShapeFactory() = default;
};
