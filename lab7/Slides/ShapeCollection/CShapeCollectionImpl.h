#pragma once

#include "../Shapes/IShape.h"

template <class Base>
class CShapeCollectionImpl : public Base
{
public:
	[[nodiscard]] std::size_t GetShapesCount() const final
	{
		return m_shapes.size();
	}

	std::shared_ptr<IShape> GetShapeAtIndex(const std::size_t index) final
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("index out of range");
		}

		return m_shapes.at(index);
	}

	void InsertShape(std::shared_ptr<IShape> const& shape, const std::size_t index) final
	{
		if (index > m_shapes.size())
		{
			throw std::out_of_range("index out of range");
		}

		m_shapes.insert(m_shapes.begin() + static_cast<int>(index), shape);
	}

	void RemoveShapeAtIndex(const std::size_t index) final
	{
		if (index >= m_shapes.size())
		{
			throw std::out_of_range("index out of range");
		}

		m_shapes.erase(m_shapes.begin() + static_cast<int>(index));
	}

protected:
	std::vector<std::shared_ptr<IShape>> m_shapes;
};
