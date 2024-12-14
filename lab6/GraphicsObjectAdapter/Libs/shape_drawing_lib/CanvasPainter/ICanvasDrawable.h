#pragma once

#include "../../graphics_lib/ICanvas.h"

namespace shape_drawing_lib
{

struct Point
{
	int x = 0;
	int y = 0;
};

class ICanvasDrawable
{
public:
	virtual void Draw(graphics_lib::ICanvas& canvas) const = 0;

	virtual ~ICanvasDrawable() = default;
};

} // namespace shape_drawing_lib
