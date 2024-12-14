#include "CTriangle.h"

shape_drawing_lib::CTriangle::CTriangle(Point const& p1, Point const& p2, Point const& p3)
	: m_p1(p1)
	, m_p2(p2)
	, m_p3(p3)
{
}

void shape_drawing_lib::CTriangle::Draw(graphics_lib::ICanvas& canvas) const
{
	canvas.MoveTo(m_p1.x, m_p1.y);
	canvas.LineTo(m_p2.x, m_p2.y);
	canvas.LineTo(m_p3.x, m_p3.y);
	canvas.LineTo(m_p1.x, m_p1.y);
}
