#include "CCanvas.h"
#include <iomanip>
#include <sstream>

CCanvas::CCanvas(std::ostream& output, const double width, const double height)
	: m_output(output)
{
	m_output << "<svg viewBox=\"0 0 " << width << " " << height << R"(" xmlns="http://www.w3.org/2000/svg">)" << std::endl;
}

CCanvas::~CCanvas()
{
	m_output << "</svg>" << std::endl;
}

void CCanvas::DrawLine(
	const PointD start,
	const PointD end,
	const std::optional<RgbaColor> color,
	const std::optional<double> thickness)
{
	std::string stroke;
	if (color.has_value())
	{
		stroke = " stroke=\"" + ColorToSvg(color.value()) + "\"";
	}

	std::string strokeWidth;
	if (thickness.has_value())
	{
		strokeWidth = " stroke-width=\"" + std::to_string(thickness.value()) + "\"";
	}

	m_output << "  <line "
			 << "x1=\"" << start.x << "\" y1=\"" << start.y << "\" "
			 << "x2=\"" << end.x << "\" y2=\"" << end.y << "\""
			 << stroke << strokeWidth
			 << " />" << std::endl;
}

void CCanvas::DrawPolygon(
	std::vector<PointD> const& points,
	const std::optional<RgbaColor> outlineColor,
	const std::optional<RgbaColor> fillColor,
	const std::optional<double> outlineThickness)
{
	std::string stroke;
	if (outlineColor.has_value())
	{
		stroke = " stroke=\"" + ColorToSvg(outlineColor.value()) + "\"";
	}

	std::string strokeWidth;
	if (outlineThickness.has_value())
	{
		strokeWidth = " stroke-width=\"" + std::to_string(outlineThickness.value()) + "\"";
	}

	std::string fill = " fill=\"none\"";
	if (fillColor.has_value())
	{
		fill = " fill=\"" + ColorToSvg(fillColor.value()) + "\"";
	}

	m_output << "  <polygon "
			 << "points=\"" << PointsToSvg(points) << "\""
			 << stroke << strokeWidth << fill
			 << " />" << std::endl;
}

void CCanvas::DrawEllipse(
	PointD const& center,
	const double horizontalRadius,
	const double verticalRadius,
	const std::optional<RgbaColor> outlineColor,
	const std::optional<RgbaColor> fillColor,
	const std::optional<double> outlineThickness)
{
	std::string stroke;
	if (outlineColor.has_value())
	{
		stroke = " stroke=\"" + ColorToSvg(outlineColor.value()) + "\"";
	}

	std::string strokeWidth;
	if (outlineThickness.has_value())
	{
		strokeWidth = " stroke-width=\"" + std::to_string(outlineThickness.value()) + "\"";
	}

	std::string fill = " fill=\"none\"";
	if (fillColor.has_value())
	{
		fill = " fill=\"" + ColorToSvg(fillColor.value()) + "\"";
	}

	m_output << "  <ellipse "
			 << "cx=\"" << center.x << "\" cy=\"" << center.y << "\" "
			 << "rx=\"" << horizontalRadius << "\" "
			 << "ry=\"" << verticalRadius << "\""
			 << stroke << strokeWidth << fill
			 << " />" << std::endl;
}

std::string CCanvas::ColorToSvg(const RgbaColor color)
{
	std::ostringstream stream;
	stream << "#" << std::hex << std::uppercase << std::setw(6) << std::setfill('0') << color;

	return stream.str();
}

std::string CCanvas::PointsToSvg(std::vector<PointD> const& points)
{
	std::ostringstream stream;
	for (const auto& [x, y] : points)
	{
		stream << x << "," << y << " ";
	}

	return stream.str();
}
