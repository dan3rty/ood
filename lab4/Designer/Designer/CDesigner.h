#pragma once

#include "../ShapeFactory/CShapeFactory.h"
#include "IDesigner.h"

class CDesigner final : public IDesigner
{
public:
	explicit CDesigner(IShapeFactory& shapeFactory);

	CPictureDraft CreateDraft(std::istream& stream, std::ostream& errorStream) override;

private:
	static constexpr char COMMENT_CHARACTER = '#';

	IShapeFactory& m_shapeFactory;
};
