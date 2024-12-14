#include "CModernGraphicsRendererCanvasAdapter.h"

app::CModernGraphicsRendererCanvasAdapter::CModernGraphicsRendererCanvasAdapter(std::ostream& output)
	: modern_graphics_lib::CModernGraphicsRenderer(output)
{
	BeginDraw();
}

app::CModernGraphicsRendererCanvasAdapter::~CModernGraphicsRendererCanvasAdapter()
{
	EndDraw();
}

void app::CModernGraphicsRendererCanvasAdapter::MoveTo(const int x, const int y)
{
	m_start.x = x;
	m_start.y = y;
}

void app::CModernGraphicsRendererCanvasAdapter::LineTo(int x, int y)
{
	DrawLine(m_start, { x, y });

	m_start.x = x;
	m_start.y = y;
}
