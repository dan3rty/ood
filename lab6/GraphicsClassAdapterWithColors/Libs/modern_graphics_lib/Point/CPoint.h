#pragma once

namespace modern_graphics_lib
{

class CPoint
{
public:
	CPoint() = default;
	CPoint(int x, int y);

	int x = 0;
	int y = 0;
};

} // namespace modern_graphics_lib
