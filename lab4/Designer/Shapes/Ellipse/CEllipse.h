#pragma once

#include "../CShape.h"

class CEllipse final : public CShape
{
public:
	CEllipse(Color color, Point const& center, double horizontalRadius, double verticalRadius);

	[[nodiscard]] Point GetCenter() const;
	[[nodiscard]] double GetHorizontalRadius() const;
	[[nodiscard]] double GetVerticalRadius() const;

	void Draw(ICanvas& canvas) const override;

private:
	Point m_center;
	double m_horizontalRadius;
	double m_verticalRadius;
};
