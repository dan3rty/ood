#pragma once
#include "Image.h"

class Drawer
{
public:
	static void DrawLine(Image& image, Point from, Point to, uint32_t color);

	static void DrawCircle(Image& image, Point center, int radius, uint32_t color);

	static void FillCircle(Image& image, Point center, int radius, uint32_t color);

private:
	static int Sign(int value);

	static void DrawSteepLine(Image& image, Point from, Point to, uint32_t color);

	static void DrawSlopeLine(Image& image, Point from, Point to, uint32_t color);
};
