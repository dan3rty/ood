#include "CRectangle.h"

CRectangle::CRectangle(PointD const& leftTop, const double width, const double height)
	: m_leftTop(leftTop)
	, m_width(width)
	, m_height(height)
{
}

std::optional<RectD> CRectangle::GetFrame() const
{
	return { {
		.leftTop = m_leftTop,
		.width = m_width,
		.height = m_height,
	} };
}

void CRectangle::SetFrame(RectD const& rect)
{
	m_leftTop = rect.leftTop;
	m_width = rect.width;
	m_height = rect.height;
}

void CRectangle::Draw(ICanvas& canvas) const
{
	const std::vector<PointD> points = {
		m_leftTop,
		{ m_leftTop.x + m_width, m_leftTop.y },
		{ m_leftTop.x + m_width, m_leftTop.y + m_height },
		{ m_leftTop.x, m_leftTop.y + m_height },
	};

	canvas.DrawPolygon(points, GetOutlineColor(), GetFillColor(), GetOutlineThickness());
}
