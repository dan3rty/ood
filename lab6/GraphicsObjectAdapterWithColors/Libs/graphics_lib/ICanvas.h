#pragma once

#include <cstdint>
namespace graphics_lib
{

using RgbColor = std::uint32_t;

class ICanvas
{
public:
	virtual void SetColor(RgbColor color) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;

	virtual ~ICanvas() = default;
};

} // namespace graphics_lib
