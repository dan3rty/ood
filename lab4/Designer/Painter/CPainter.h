#pragma once

#include "../PictureDraft/CPictureDraft.h"

class CPainter
{
public:
	static void DrawPicture(CPictureDraft const& draft, ICanvas& canvas);
};
