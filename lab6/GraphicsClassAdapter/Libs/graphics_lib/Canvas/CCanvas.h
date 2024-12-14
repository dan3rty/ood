#pragma once

#include "../ICanvas.h"

namespace graphics_lib
{

class CCanvas final : public ICanvas
{
public:
	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;
};

} // namespace graphics_lib
