#pragma once

#include "../../Shapes/ShapeTypes.h"
#include <optional>
#include <vector>

class ICanvas
{
public:
	virtual void DrawLine(
		PointD start,
		PointD end,
		std::optional<RgbaColor> color,
		std::optional<double> thickness)
		= 0;

	virtual void DrawPolygon(
		std::vector<PointD> const& points,
		std::optional<RgbaColor> outlineColor,
		std::optional<RgbaColor> fillColor,
		std::optional<double> outlineThickness)
		= 0;

	virtual void DrawEllipse(
		PointD const& center,
		double horizontalRadius,
		double verticalRadius,
		std::optional<RgbaColor> outlineColor,
		std::optional<RgbaColor> fillColor,
		std::optional<double> outlineThickness)
		= 0;

	virtual ~ICanvas() = default;
};
