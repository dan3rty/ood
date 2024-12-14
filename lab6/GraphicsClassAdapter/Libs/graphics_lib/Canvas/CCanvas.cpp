#include "CCanvas.h"
#include <iostream>

void graphics_lib::CCanvas::MoveTo(const int x, const int y)
{
	std::cout << "MoveTo (" << x << ", " << y << ")\n";
}

void graphics_lib::CCanvas::LineTo(const int x, const int y)
{
	std::cout << "LineTo (" << x << ", " << y << ")\n";
}
