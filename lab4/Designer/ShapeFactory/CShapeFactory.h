#pragma once

#include "../ShapeFactory/IShapeFactory.h"
#include <functional>
#include <sstream>
#include <unordered_map>
#include <vector>

class CShapeFactory final : public IShapeFactory
{
public:
	CShapePtr CreateShape(const std::string& description) override;

private:
	using Args = std::vector<std::string>;
	using ShapeCreator = std::function<CShapePtr(std::istream&)>;

	static inline const std::unordered_map<std::string, Color> ARG_TO_COLOR_MAP = {
		{ "red", Color::Red },
		{ "green", Color::Green },
		{ "blue", Color::Blue },
		{ "pink", Color::Pink },
		{ "yellow", Color::Yellow },
		{ "black", Color::Black },
		{ "gray", Color::Gray },
		{ "white", Color::White },
	};

	static ShapeCreator GetShapeCreator(std::string const& shapeType);
	static Color ParseColor(std::istream& stream);

	static CShapePtr CreateEllipse(std::istream& args);
	static CShapePtr CreateRectangle(std::istream& args);
	static CShapePtr CreateRegularPolygon(std::istream& args);
	static CShapePtr CreateTriangle(std::istream& args);
};
