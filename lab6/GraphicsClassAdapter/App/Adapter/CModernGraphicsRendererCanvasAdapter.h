#pragma once

#include "../../Libs/graphics_lib/ICanvas.h"
#include "../../Libs/modern_graphics_lib/ModernGraphicsRenderer/CModernGraphicsRenderer.h"

namespace app
{

class CModernGraphicsRendererCanvasAdapter final : public graphics_lib::ICanvas
	, private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	explicit CModernGraphicsRendererCanvasAdapter(std::ostream& output);

	~CModernGraphicsRendererCanvasAdapter() override;

	void MoveTo(int x, int y) override;
	void LineTo(int x, int y) override;

private:
	modern_graphics_lib::CPoint m_start;
};

} // namespace app
