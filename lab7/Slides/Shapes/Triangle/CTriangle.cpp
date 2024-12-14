#include "CTriangle.h"

CTriangle::CTriangle(PointD const& vertex1, PointD const& vertex2, PointD const& vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

std::optional<RectD> CTriangle::GetFrame() const
{
	auto const& [minX, maxX] = std::minmax({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	auto const& [minY, maxY] = std::minmax({ m_vertex1.y, m_vertex2.y, m_vertex3.y });

	return { {
		.leftTop = { minX, minY },
		.width = maxX - minX,
		.height = maxY - minY,
	} };
}

void CTriangle::SetFrame(RectD const& rect)
{
	const auto currentFrame = GetFrame().value();

	const auto scaleFactorX = rect.width / currentFrame.width;
	const auto scaleFactorY = rect.height / currentFrame.height;

	ScalePoint(m_vertex1, currentFrame, rect, scaleFactorX, scaleFactorY);
	ScalePoint(m_vertex2, currentFrame, rect, scaleFactorX, scaleFactorY);
	ScalePoint(m_vertex3, currentFrame, rect, scaleFactorX, scaleFactorY);
}

void CTriangle::Draw(ICanvas& canvas) const
{
	canvas.DrawPolygon(
		{ m_vertex1, m_vertex2, m_vertex3 },
		GetOutlineColor(),
		GetFillColor(),
		GetOutlineThickness());
}

void CTriangle::ScalePoint(
	PointD& point,
	RectD const& initialFrame,
	RectD const& newFrame,
	const double scaleFactorX,
	const double scaleFactorY)
{
	point.x = newFrame.leftTop.x + (point.x - initialFrame.leftTop.x) * scaleFactorX;
	point.y = newFrame.leftTop.y + (point.y - initialFrame.leftTop.y) * scaleFactorY;
}
