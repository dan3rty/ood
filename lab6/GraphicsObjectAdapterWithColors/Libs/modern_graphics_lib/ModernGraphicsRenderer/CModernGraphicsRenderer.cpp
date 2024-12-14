#include "CModernGraphicsRenderer.h"
#include <iomanip>

modern_graphics_lib::CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream& output)
	: m_output(output)
{
}

modern_graphics_lib::CModernGraphicsRenderer::~CModernGraphicsRenderer() noexcept
{
	if (m_drawing)
	{
		EndDraw();
	}
}

void modern_graphics_lib::CModernGraphicsRenderer::BeginDraw()
{
	if (m_drawing)
	{
		throw std::logic_error("drawing has already begun");
	}

	m_output << "<draw>\n";
	m_drawing = true;
}

void modern_graphics_lib::CModernGraphicsRenderer::DrawLine(CPoint const& start, CPoint const& end, CRgbaColor const& color)
{
	if (!m_drawing)
	{
		throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}

	m_output << "  <line fromX=\"" << start.x << "\" fromY=\"" << start.y << "\" "
			 << "toX=\"" << end.x << "\" toY=\"" << end.y << "\">\n  ";
	ApplyColor(color);
	m_output << "  </line>\n";
}

void modern_graphics_lib::CModernGraphicsRenderer::EndDraw()
{
	if (!m_drawing)
	{
		throw std::logic_error("drawing has not been started");
	}

	m_output << "</draw>\n";
	m_drawing = false;
}

void modern_graphics_lib::CModernGraphicsRenderer::ApplyColor(CRgbaColor const& color)
{
	std::ios oldState(nullptr);
	oldState.copyfmt(m_output);

	m_output << "  <color r=\""
			 << std::fixed << std::setprecision(1)
			 << color.r << "\" g=\"" << color.g << "\" b=\"" << color.b
			 << std::fixed << std::setprecision(2)
			 << "\" a=\"" << color.a << "\"/>\n";

	m_output.copyfmt(oldState);
}
