#include "CModernGraphicsRenderer.h"

modern_graphics_lib::CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream& output)
	: m_output(output)
{
}

modern_graphics_lib::CModernGraphicsRenderer::~CModernGraphicsRenderer()
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

void modern_graphics_lib::CModernGraphicsRenderer::DrawLine(modern_graphics_lib::CPoint const& start, modern_graphics_lib::CPoint const& end)
{
	if (!m_drawing)
	{
		throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}

	m_output << "  <line fromX=\"" << start.x << "\" fromY=\"" << start.y << "\" "
			 << "toX=\"" << end.x << "\" toY=\"" << end.y << "\"/>\n";
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
