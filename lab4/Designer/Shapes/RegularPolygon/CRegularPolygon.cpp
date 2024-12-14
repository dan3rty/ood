#include "CRegularPolygon.h"
#include <cmath>

CRegularPolygon::CRegularPolygon(const Color color, const std::size_t vertexCount, const Point& center, const double radius)
	: CShape(color)
	, m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
	if (m_vertexCount < MIN_VERTICES_COUNT)
	{
		throw std::invalid_argument("regular polygon must contain at least " + std::to_string(MIN_VERTICES_COUNT) + " vertices");
	}
}

std::size_t CRegularPolygon::GetVertexCount() const
{
	return m_vertexCount;
}

Point CRegularPolygon::GetCenter() const
{
	return m_center;
}

double CRegularPolygon::GetRadius() const
{
	return m_radius;
}

void CRegularPolygon::Draw(ICanvas& canvas) const
{
	canvas.SetColor(GetColor());

	auto const vertices = CalculateVertices();
	for (std::size_t i = 0; i < vertices.size() - 1; ++i)
	{
		canvas.DrawLine(vertices[i], vertices[i + 1]);
	}
	canvas.DrawLine(vertices[vertices.size() - 1], vertices[0]);
}

std::vector<Point> CRegularPolygon::CalculateVertices() const
{
	std::vector<Point> result;
	const auto vertexAngle = 2 * M_PI / static_cast<double>(m_vertexCount);

	result.reserve(m_vertexCount);
	for (std::size_t i = 0; i < m_vertexCount; ++i)
	{
		result.push_back({
			m_center.x + m_radius * std::cos(vertexAngle * static_cast<double>(i)),
			m_center.y + m_radius * std::sin(vertexAngle * static_cast<double>(i)),
		});
	}

	return result;
}
