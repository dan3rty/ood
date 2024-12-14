#pragma once

namespace modern_graphics_lib
{

class CRgbaColor
{
public:
	CRgbaColor() = default;
	CRgbaColor(float r, float g, float b, float a);

	float r = 0;
	float g = 0;
	float b = 0;
	float a = 1;
};

} // namespace modern_graphics_lib
