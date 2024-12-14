#pragma once

#include "../Shape/CShape.h"

class CTriangle final : public CShape
{
public:
	CTriangle(PointD const& vertex1, PointD const& vertex2, PointD const& vertex3);

	[[nodiscard]] std::optional<RectD> GetFrame() const override;
	void SetFrame(RectD const& rect) override;

	void Draw(ICanvas& canvas) const override;

private:
	static void ScalePoint(
		PointD& point,
		RectD const& initialFrame,
		RectD const& newFrame,
		double scaleFactorX,
		double scaleFactorY);

	PointD m_vertex1;
	PointD m_vertex2;
	PointD m_vertex3;
};
