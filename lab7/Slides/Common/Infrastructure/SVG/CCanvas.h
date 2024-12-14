#pragma once

 #include "../../App/ICanvas.h"
#include <iostream>

class CCanvas final : public ICanvas
{
public:
	CCanvas(std::ostream& output, double width, double height);
	~CCanvas() override;

	void DrawLine(
		PointD start,
		PointD end,
		std::optional<RgbaColor> color,
		std::optional<double> thickness) override;

	void DrawPolygon(
		std::vector<PointD> const& points,
		std::optional<RgbaColor> outlineColor,
		std::optional<RgbaColor> fillColor,
		std::optional<double> outlineThickness) override;

	void DrawEllipse(
		PointD const& center,
		double horizontalRadius,
		double verticalRadius,
		std::optional<RgbaColor> outlineColor,
		std::optional<RgbaColor> fillColor,
		std::optional<double> outlineThickness) override;

private:
	static std::string ColorToSvg(RgbaColor color);
	static std::string PointsToSvg(std::vector<PointD> const& points);

	std::ostream& m_output;
};
