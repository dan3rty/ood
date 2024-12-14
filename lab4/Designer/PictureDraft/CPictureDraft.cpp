#include "CPictureDraft.h"

bool CPictureDraft::IsEmpty() const
{
	return m_shapes.empty();
}

void CPictureDraft::AddShape(CShapePtr&& shape)
{
	m_shapes.push_back(std::move(shape));
}

CPictureDraft::Storage::const_iterator CPictureDraft::begin() const
{
	return m_shapes.begin();
}

CPictureDraft::Storage::const_iterator CPictureDraft::end() const
{
	return m_shapes.end();
}
