#include "CPainter.h"

void CPainter::DrawPicture(CPictureDraft const& draft, ICanvas& canvas)
{
	for (auto&& shape : draft)
	{
		shape->Draw(canvas);
	}
}
