#pragma once
#include "./CoW.h"
#include "./Geom.h"
#include "./Tile.h"
#include <vector>

class Image
{
public:
	explicit Image(Size size, uint32_t color = 0xFFFFFF);

	[[nodiscard]] Size GetSize() const noexcept;

	[[nodiscard]] uint32_t GetPixel(Point p) const noexcept;

	void SetPixel(Point p, uint32_t color);

private:
	Size m_size;
	std::vector<std::vector<CoW<Tile>>> m_tiles;
};
