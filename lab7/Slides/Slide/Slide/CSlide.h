#pragma once

#include "../ISlide.h"

class CSlide final : public ISlide
{
public:
	CSlide(double width, double height);

	[[nodiscard]] double GetWidth() const override;
	[[nodiscard]] double GetHeight() const override;

	[[nodiscard]] IShapeCollection& GetShapes() const override;

	void Draw(ICanvas& canvas) const override;

private:
	double m_width;
	double m_height;
	std::unique_ptr<IShapeCollection> m_shapes;
};
