#include "CShapeFactory.h"
#include "../Shapes/Ellipse/CEllipse.h"
#include "../Shapes/Rectangle/CRectangle.h"
#include "../Shapes/RegularPolygon/CRegularPolygon.h"
#include "../Shapes/Triangle/CTriangle.h"

CShapePtr CShapeFactory::CreateShape(std::string const& description)
{
	std::istringstream args(description);

	std::string shapeType;
	args >> shapeType;

	auto const creator = GetShapeCreator(shapeType);

	return creator(args);
}

CShapeFactory::ShapeCreator CShapeFactory::GetShapeCreator(std::string const& shapeType)
{
	if (shapeType == "ellipse")
	{
		return CreateEllipse;
	}
	if (shapeType == "rectangle")
	{
		return CreateRectangle;
	}
	if (shapeType == "regular-polygon")
	{
		return CreateRegularPolygon;
	}
	if (shapeType == "triangle")
	{
		return CreateTriangle;
	}

	throw std::invalid_argument("unknown shape: " + shapeType);
}

Color CShapeFactory::ParseColor(std::istream& stream)
{
	std::string value;
	stream >> value;

	auto const color = ARG_TO_COLOR_MAP.find(value);
	if (color == ARG_TO_COLOR_MAP.end())
	{
		throw std::invalid_argument("invalid color: " + value);
	}

	return color->second;
}

CShapePtr CShapeFactory::CreateEllipse(std::istream& args)
{
	auto const color = ParseColor(args);
	double x, y, horizontalRadius, verticalRadius;
	args >> x >> y >> horizontalRadius >> verticalRadius;

	if (args.bad() || args.fail())
	{
		throw std::invalid_argument("invalid arguments for ellipse");
	}

	return std::make_unique<CEllipse>(
		color,
		Point{ x, y },
		horizontalRadius,
		verticalRadius);
}

CShapePtr CShapeFactory::CreateRectangle(std::istream& args)
{
	auto const color = ParseColor(args);
	double x, y, width, height;
	args >> x >> y >> width >> height;

	if (args.bad() || args.fail())
	{
		throw std::invalid_argument("invalid arguments for rectangle");
	}

	return std::make_unique<CRectangle>(
		color,
		Point{ x, y },
		width,
		height);
}

CShapePtr CShapeFactory::CreateRegularPolygon(std::istream& args)
{
	auto const color = ParseColor(args);
	double vertexCount, x, y, radius;
	args >> vertexCount >> x >> y >> radius;

	if (args.bad() || args.fail())
	{
		throw std::invalid_argument("invalid arguments for regular polygon");
	}

	return std::make_unique<CRegularPolygon>(
		color,
		vertexCount,
		Point{ x, y },
		radius);
}

CShapePtr CShapeFactory::CreateTriangle(std::istream& args)
{
	auto const color = ParseColor(args);
	double x1, y1, x2, y2, x3, y3;
	args >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

	if (args.bad() || args.fail())
	{
		throw std::invalid_argument("invalid arguments for triangle");
	}

	return std::make_unique<CTriangle>(
		color,
		Point{ x1, y1 },
		Point{ x2, y2 },
		Point{ x3, y3 });
}
