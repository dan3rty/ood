#pragma once

bool ApproximatelyEqual(double a, double b);

enum class Color
{
	Red,
	Green,
	Blue,
	Pink,
	Yellow,
	Black,
	White,
	Gray,
};

struct Point
{
	double x = 0;
	double y = 0;

	bool operator==(Point const& other) const;
};
