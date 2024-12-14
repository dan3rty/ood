#include "CCanvas.h"

CCanvas::CCanvas(std::ostream& output)
	: m_output(output)
{
	m_output << "<svg viewBox=\"0 0 800 600\" xmlns=\"http://www.w3.org/2000/svg\">\n";
}

CCanvas::~CCanvas()
{
	m_output << "</svg>\n";
}

void CCanvas::SetColor(const Color color)
{
	switch (color)
	{
	case Color::Red:
		m_currentColor = "red";
		break;
	case Color::Green:
		m_currentColor = "green";
		break;
	case Color::Blue:
		m_currentColor = "blue";
		break;
	case Color::Pink:
		m_currentColor = "pink";
		break;
	case Color::Yellow:
		m_currentColor = "yellow";
		break;
	case Color::Black:
		m_currentColor = "black";
		break;
	default:
		break;
	}
}

void CCanvas::DrawLine(const Point& from, const Point& to)
{
	m_output << "  <line x1=\""
			 << from.x << "\" y1=\"" << from.y << "\" x2=\""
			 << to.x << "\" y2=\"" << to.y << "\" stroke=\""
			 << m_currentColor << "\" />\n";
}

void CCanvas::DrawEllipse(const Point& center, const double horizontalRadius, const double verticalRadius)
{
	m_output << "  <ellipse cx=\""
			 << center.x << "\" cy=\"" << center.y << "\" rx=\""
			 << horizontalRadius << "\" ry=\"" << verticalRadius << "\" stroke=\""
			 << m_currentColor << "\" fill=\"none\" />\n";
}
