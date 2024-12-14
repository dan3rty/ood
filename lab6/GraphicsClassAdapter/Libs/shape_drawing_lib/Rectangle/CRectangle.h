#pragma once

#include "../CanvasPainter/ICanvasDrawable.h"

namespace shape_drawing_lib
{

class CRectangle final : public ICanvasDrawable
{
public:
	CRectangle(Point const& leftTop, int width, int height);

	void Draw(graphics_lib::ICanvas& canvas) const override;

private:
	Point m_leftTop;
	int m_width;
	int m_height;
};

} // namespace shape_drawing_lib
