#include "CCanvasPainter.h"

shape_drawing_lib::CCanvasPainter::CCanvasPainter(graphics_lib::ICanvas& canvas)
	: m_canvas(canvas)
{
}

void shape_drawing_lib::CCanvasPainter::Draw(shape_drawing_lib::ICanvasDrawable const& drawable) const
{
	drawable.Draw(m_canvas);
}
