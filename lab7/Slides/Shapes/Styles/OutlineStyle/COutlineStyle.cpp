#include "COutlineStyle.h"

std::optional<double> COutlineStyle::GetThickness() const
{
	return m_thickness;
}

void COutlineStyle::SetThickness(const double thickness)
{
	m_thickness = thickness;
}
