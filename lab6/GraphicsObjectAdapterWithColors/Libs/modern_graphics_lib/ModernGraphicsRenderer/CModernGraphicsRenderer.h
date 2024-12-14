#pragma once

#include "../Point/CPoint.h"
#include "../RgbaColor/CRgbaColor.h"
#include <iostream>

namespace modern_graphics_lib
{

class CModernGraphicsRenderer
{
public:
	explicit CModernGraphicsRenderer(std::ostream& output);

	~CModernGraphicsRenderer() noexcept;

	void BeginDraw();
	void DrawLine(CPoint const& start, CPoint const& end, CRgbaColor const& color);
	void EndDraw();

private:
	void ApplyColor(CRgbaColor const& color);

	std::ostream& m_output;
	bool m_drawing = false;
};

} // namespace modern_graphics_lib
