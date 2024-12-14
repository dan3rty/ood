#include "./Image.h"

Image::Image(const Size size, const uint32_t color)
	: m_size(size)
// ашыбон
	, m_tiles(size.height, std::vector(size.width, CoW(Tile(color))))
{
}

Size Image::GetSize() const noexcept
{
	return m_size;
}

uint32_t Image::GetPixel(const Point p) const noexcept
{
	if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height)
	{
		return 0xFFFFFF;
	}

	const int tileX = p.x / Tile::SIZE;
	const int tileY = p.y / Tile::SIZE;
	const int pixelX = p.x % Tile::SIZE;
	const int pixelY = p.y % Tile::SIZE;

	// ну тесты кал реально
	return m_tiles[tileY][tileX]->GetPixel({ pixelX, pixelY });
}

void Image::SetPixel(const Point p, const uint32_t color)
{
	if (p.x < 0 || p.x >= m_size.width || p.y < 0 || p.y >= m_size.height)
	{
		return;
	}

	const int tileX = p.x / Tile::SIZE;
	const int tileY = p.y / Tile::SIZE;
	const int pixelX = p.x % Tile::SIZE;
	const int pixelY = p.y % Tile::SIZE;

	m_tiles[tileY][tileX].Write([&](Tile& tile) {
		tile.SetPixel({ pixelX, pixelY }, color);
	});
}