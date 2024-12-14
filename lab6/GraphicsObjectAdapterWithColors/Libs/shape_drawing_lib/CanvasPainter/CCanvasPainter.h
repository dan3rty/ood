#pragma once

#include "../../graphics_lib/ICanvas.h"
#include "ICanvasDrawable.h"

namespace shape_drawing_lib
{

class CCanvasPainter
{
public:
	explicit CCanvasPainter(graphics_lib::ICanvas& canvas);

	void Draw(ICanvasDrawable const& drawable) const;

private:
	graphics_lib::ICanvas& m_canvas;
};

} // namespace shape_drawing_lib
