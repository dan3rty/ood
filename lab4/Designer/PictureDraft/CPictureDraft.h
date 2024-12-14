#pragma once

#include "../Shapes/CShape.h"
#include <vector>

class CPictureDraft
{
public:
	using Storage = std::vector<CShapePtr>;

	void AddShape(CShapePtr&& shape);
	[[nodiscard]] bool IsEmpty() const;

	[[nodiscard]] Storage::const_iterator begin() const;
	[[nodiscard]] Storage::const_iterator end() const;

private:
	Storage m_shapes;
};
