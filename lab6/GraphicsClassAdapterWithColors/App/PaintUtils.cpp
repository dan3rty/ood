#include "PaintUtils.h"
#include "../Libs/graphics_lib/Canvas/CCanvas.h"
#include "../Libs/modern_graphics_lib/ModernGraphicsRenderer/CModernGraphicsRenderer.h"
#include "../Libs/shape_drawing_lib/Rectangle/CRectangle.h"
#include "../Libs/shape_drawing_lib/Triangle/CTriangle.h"
#include "Adapter/CModernGraphicsRendererCanvasAdapter.h"

void app::PaintPicture(const shape_drawing_lib::CCanvasPainter& painter)
{
	const shape_drawing_lib::CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 0xFF1233);
	const shape_drawing_lib::CRectangle rectangle({ 30, 40 }, 18, 24, 0x00FF12);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void app::PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	const shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void app::PaintPictureOnModernGraphicsRenderer()
{
	CModernGraphicsRendererCanvasAdapter adapter(std::cout);
	shape_drawing_lib::CCanvasPainter painter(adapter);

	PaintPicture(painter);
}
