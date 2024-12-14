#pragma once

#include "../Point/CPoint.h"
#include <iostream>

namespace modern_graphics_lib
{

class CModernGraphicsRenderer
{
public:
	explicit CModernGraphicsRenderer(std::ostream& output);

	~CModernGraphicsRenderer();

	void BeginDraw();
	void DrawLine(CPoint const& start, CPoint const& end) const;
	void EndDraw();

private:
	std::ostream& m_output;
	bool m_drawing = false;
};

} // namespace modern_graphics_lib
