#pragma once

#include "../Shapes/ShapeTypes.h"
#include "ICanvas.h"
#include <iostream>

class CCanvas : public ICanvas
{
public:
	explicit CCanvas(std::ostream& output);
	~CCanvas() override;
	void SetColor(Color color) override;
	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(const Point& center, double horizontalRadius, double verticalRadius) override;

private:
	std::ostream& m_output;
	std::string m_currentColor = "black";
};
