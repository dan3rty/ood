#pragma once

#include "../Libs/shape_drawing_lib/CanvasPainter/CCanvasPainter.h"

namespace app
{

void PaintPicture(const shape_drawing_lib::CCanvasPainter& painter);
void PaintPictureOnCanvas();

void PaintPictureOnModernGraphicsRenderer();

}
