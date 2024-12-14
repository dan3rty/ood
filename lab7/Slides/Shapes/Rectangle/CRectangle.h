#pragma once

#include "../Shape/CShape.h"

class CRectangle final : public CShape
{
public:
	CRectangle(PointD const& leftTop, double width, double height);

	[[nodiscard]] std::optional<RectD> GetFrame() const override;
	void SetFrame(RectD const& rect) override;

	void Draw(ICanvas& canvas) const override;

private:
	PointD m_leftTop;
	double m_width;
	double m_height;
};
