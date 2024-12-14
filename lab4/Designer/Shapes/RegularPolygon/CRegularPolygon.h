#pragma once

#include "../CShape.h"
#include <vector>

class CRegularPolygon final : public CShape
{
public:
	CRegularPolygon(Color color, std::size_t vertexCount, Point const& center, double radius);

	[[nodiscard]] std::size_t GetVertexCount() const;
	[[nodiscard]] Point GetCenter() const;
	[[nodiscard]] double GetRadius() const;

	void Draw(ICanvas& canvas) const override;

private:
	static constexpr std::size_t MIN_VERTICES_COUNT = 2;

	[[nodiscard]] std::vector<Point> CalculateVertices() const;

	std::size_t m_vertexCount;
	Point m_center;
	double m_radius;
};
