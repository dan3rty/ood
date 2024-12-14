#include "ShapeTypes.h"
#include <cmath>
#include <limits>

bool ApproximatelyEqual(const double a, const double b)
{
	return std::abs(a - b) < std::numeric_limits<double>::epsilon();
}

bool Point::operator==(Point const& other) const
{
	return ApproximatelyEqual(x, other.x) && ApproximatelyEqual(y, other.y);
}
