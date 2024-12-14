#pragma once

#include "../IShape.h"

class CShape : public IShape
{
public:
	CShape();

	std::shared_ptr<IOutlineStyle> GetOutlineStyle() final;
	[[nodiscard]] std::shared_ptr<IOutlineStyle const> GetOutlineStyle() const final;

	std::shared_ptr<IStyle> GetFillStyle() final;
	[[nodiscard]] std::shared_ptr<IStyle const> GetFillStyle() const final;

	std::shared_ptr<IShapeGroup> GetGroup() final;
	[[nodiscard]] std::shared_ptr<IShapeGroup const> GetGroup() const final;

protected:
	[[nodiscard]] std::optional<RgbaColor> GetOutlineColor() const;
	[[nodiscard]] std::optional<double> GetOutlineThickness() const;
	[[nodiscard]] std::optional<RgbaColor> GetFillColor() const;

private:
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};
