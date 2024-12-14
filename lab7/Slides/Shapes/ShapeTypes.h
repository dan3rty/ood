#pragma once

#include <cstdint>

using RgbaColor = std::uint32_t;

template <typename T>
struct Point
{
	T x;
	T y;

	bool operator==(Point const& other) const
	{
		return x == other.x && y == other.y;
	}
};

using PointD = Point<double>;

template <typename T>
struct Rect
{
	T Top() const
	{
		return leftTop.y;
	}

	T Right() const
	{
		return leftTop.x + width;
	}

	T Bottom() const
	{
		return leftTop.y + height;
	}

	T Left() const
	{
		return leftTop.x;
	}

	bool operator==(Rect const& other) const
	{
		return leftTop == other.leftTop && width == other.width && height == other.height;
	}

	Point<T> leftTop;
	T width;
	T height;
};

using RectD = Rect<double>;
