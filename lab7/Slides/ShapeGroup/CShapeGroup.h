#pragma once

#include "../ShapeCollection/CShapeCollectionImpl.h"
#include "IShapeGroup.h"

class CShapeGroup final : public CShapeCollectionImpl<IShapeGroup>
{
public:
	explicit CShapeGroup();

	[[nodiscard]] std::optional<RectD> GetFrame() const override;
	void SetFrame(RectD const& rect) override;

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() override;
	[[nodiscard]] std::shared_ptr<IOutlineStyle const> GetOutlineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	[[nodiscard]] std::shared_ptr<IStyle const> GetFillStyle() const override;

	std::shared_ptr<IShapeGroup> GetGroup() override;
	[[nodiscard]] std::shared_ptr<IShapeGroup const> GetGroup() const override;

	void Draw(ICanvas& canvas) const override;

private:
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};
