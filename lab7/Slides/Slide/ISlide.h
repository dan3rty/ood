#pragma once

#include "../Common/App/IDrawable.h"
#include "../ShapeCollection/IShapeCollection.h"

class ISlide : public IDrawable
{
public:
	[[nodiscard]] virtual double GetWidth() const = 0;
	[[nodiscard]] virtual double GetHeight() const = 0;

	[[nodiscard]] virtual IShapeCollection& GetShapes() const = 0;
};
