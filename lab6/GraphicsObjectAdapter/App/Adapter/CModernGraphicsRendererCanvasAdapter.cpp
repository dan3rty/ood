#include "CModernGraphicsRendererCanvasAdapter.h"

app::CModernGraphicsRendererCanvasAdapter::CModernGraphicsRendererCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
	: m_renderer(renderer)
{
}

void app::CModernGraphicsRendererCanvasAdapter::MoveTo(const int x, const int y)
{
	m_start.x = x;
	m_start.y = y;
}

void app::CModernGraphicsRendererCanvasAdapter::LineTo(int x, int y)
{
	m_renderer.DrawLine(m_start, { x, y });

	m_start.x = x;
	m_start.y = y;
}
