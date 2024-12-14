#include "CShape.h"
#include "../Styles/FillStyle/CFillStyle.h"
#include "../Styles/OutlineStyle/COutlineStyle.h"

CShape::CShape()
	: m_outlineStyle(std::make_shared<COutlineStyle>())
	, m_fillStyle(std::make_shared<CFillStyle>())
{
}

std::shared_ptr<IOutlineStyle> CShape::GetOutlineStyle()
{
	return m_outlineStyle;
}

std::shared_ptr<IOutlineStyle const> CShape::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> CShape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<IStyle const> CShape::GetFillStyle() const
{
	return m_fillStyle;
}

std::optional<RgbaColor> CShape::GetOutlineColor() const
{
	std::optional<RgbaColor> outlineColor = std::nullopt;
	if (m_outlineStyle->IsEnabled())
	{
		outlineColor = m_outlineStyle->GetColor();
	}

	return outlineColor;
}

std::optional<double> CShape::GetOutlineThickness() const
{
	std::optional<double> thickness = std::nullopt;
	if (m_outlineStyle->IsEnabled())
	{
		thickness = m_outlineStyle->GetThickness();
	}

	return thickness;
}

std::optional<RgbaColor> CShape::GetFillColor() const
{
	std::optional<RgbaColor> fillColor = std::nullopt;
	if (m_fillStyle->IsEnabled())
	{
		fillColor = m_fillStyle->GetColor();
	}

	return fillColor;
}

std::shared_ptr<IShapeGroup> CShape::GetGroup()
{
	return nullptr;
}

std::shared_ptr<IShapeGroup const> CShape::GetGroup() const
{
	return nullptr;
}
