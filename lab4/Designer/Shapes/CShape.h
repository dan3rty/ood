#pragma once

#include "../Canvas/ICanvas.h"
#include "ShapeTypes.h"

#include <memory>

class CShape
{
public:
	explicit CShape(Color color);

	[[nodiscard]] Color GetColor() const;

	virtual void Draw(ICanvas& canvas) const = 0;

	virtual ~CShape() = default;

private:
	Color m_color;
};

using CShapePtr = std::unique_ptr<CShape>;
