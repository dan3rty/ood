#include "CRectangle.h"

shape_drawing_lib::CRectangle::CRectangle(Point const& leftTop, const int width, const int height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

void shape_drawing_lib::CRectangle::Draw(graphics_lib::ICanvas& canvas) const
{
	canvas.MoveTo(m_leftTop.x, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
	canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
	canvas.LineTo(m_leftTop.x, m_leftTop.y);
}
