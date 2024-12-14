#pragma once

#include "../Shapes/IShape.h"

class IShapeCollection
{
public:
	[[nodiscard]] virtual std::size_t GetShapesCount() const = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(std::size_t index) = 0;
	virtual void InsertShape(std::shared_ptr<IShape> const& shape, std::size_t index) = 0;
	virtual void RemoveShapeAtIndex(std::size_t index) = 0;

	virtual ~IShapeCollection() = default;
};
