#pragma once
#include "./Geom.h"
#include <array>
#include <cassert>
#include <cstdint>

// суметь нарисовать разновидности прокси

class Tile
{
public:
	constexpr static int SIZE = 8;

	explicit Tile(const uint32_t color = 0xFFFFFF) noexcept
	{
		for (int y = 0; y < SIZE; ++y)
		{
			for (int x = 0; x < SIZE; ++x)
			{
				m_pixels[y][x] = color;
			}
		}

		// -------------- не удалять ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount;
		// -------------- не удалять ------------
	}

	Tile(const Tile& other)
	{
		m_pixels = other.m_pixels;

		// -------------- не удалять ------------
		assert(m_instanceCount >= 0);
		++m_instanceCount;
		// -------------- не удалять ------------
	}

	~Tile()
	{
		// -------------- не удалять ------------
		--m_instanceCount;
		assert(m_instanceCount >= 0);
		// -------------- не удалять ------------
	}

	void SetPixel(const Point p, const uint32_t color) noexcept
	{
		if (p.x >= 0 && p.x < SIZE && p.y >= 0 && p.y < SIZE)
		{
			m_pixels[p.y][p.x] = color;
		}
	}

	[[nodiscard]] uint32_t GetPixel(const Point p) const noexcept
	{
		if (p.x >= 0 && p.x < SIZE && p.y >= 0 && p.y < SIZE)
		{
			return m_pixels[p.y][p.x];
		}
		return 0xFFFFFF;
	}

	static int GetInstanceCount() noexcept
	{
		// -------------- не удалять ------------
		return m_instanceCount;
		// -------------- не удалять ------------
	}

private:
	// -------------- не удалять ------------
	inline static int m_instanceCount = 0;
	// -------------- не удалять ------------

    std::array<std::array<uint32_t, SIZE>, SIZE> m_pixels{};
};