#pragma once

#include "../CanvasPainter/ICanvasDrawable.h"

namespace shape_drawing_lib
{

class CTriangle final : public ICanvasDrawable
{
public:
	CTriangle(Point const& p1, Point const& p2, Point const& p3);

	void Draw(graphics_lib::ICanvas& canvas) const override;

private:
	Point m_p1;
	Point m_p2;
	Point m_p3;
};

} // namespace shape_drawing_lib
