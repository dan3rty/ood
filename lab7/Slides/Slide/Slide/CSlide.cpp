#include "CSlide.h"
#include "../../ShapeCollection/CShapeCollection.h"

CSlide::CSlide(const double width, const double height)
	: m_width(width)
	, m_height(height)
	, m_shapes(std::make_unique<CShapeCollection>())
{
}

double CSlide::GetWidth() const
{
	return m_width;
}

double CSlide::GetHeight() const
{
	return m_height;
}

IShapeCollection& CSlide::GetShapes() const
{
	return *m_shapes;
}

void CSlide::Draw(ICanvas& canvas) const
{
	for (std::size_t i = 0; i < m_shapes->GetShapesCount(); ++i)
	{
		m_shapes->GetShapeAtIndex(i)->Draw(canvas);
	}
}
