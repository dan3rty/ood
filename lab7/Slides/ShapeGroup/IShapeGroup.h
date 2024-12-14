#pragma once

#include "../ShapeCollection/IShapeCollection.h"
#include "../Shapes/IShape.h"

class IShapeGroup : public IShape
	, public IShapeCollection
{
};
