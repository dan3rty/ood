#include "CModernGraphicsRendererCanvasAdapter.h"

app::CModernGraphicsRendererCanvasAdapter::CModernGraphicsRendererCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer& renderer)
	: m_renderer(renderer)
{
}

void app::CModernGraphicsRendererCanvasAdapter::SetColor(const graphics_lib::RgbColor color)
{
	m_color.r = static_cast<float>((color >> 16) & 0xFF) / 255;
	m_color.g = static_cast<float>((color >> 8) & 0xFF) / 255;
	m_color.b = static_cast<float>(color & 0xFF) / 255;
}

void app::CModernGraphicsRendererCanvasAdapter::MoveTo(const int x, const int y)
{
	m_start.x = x;
	m_start.y = y;
}

void app::CModernGraphicsRendererCanvasAdapter::LineTo(int x, int y)
{
	m_renderer.DrawLine(m_start, { x, y }, m_color);

	m_start.x = x;
	m_start.y = y;
}
