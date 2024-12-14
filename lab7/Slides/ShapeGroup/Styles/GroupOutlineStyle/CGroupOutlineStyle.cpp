#include "CGroupOutlineStyle.h"

CGroupOutlineStyle::CGroupOutlineStyle(OutlineStyleEnumerator&& enumerator)
	: CGroupStyleImpl(std::move(enumerator))
{
}

std::optional<double> CGroupOutlineStyle::GetThickness() const
{
	std::optional<double> thickness;
	bool sequential = false;

	// устранить дублирорвание
	m_enumerator([&thickness, &sequential](const IOutlineStyle& style) {
		if (!sequential)
		{
			// тесты бы починить
			thickness = style.GetThickness();
			sequential = true;
		}

		if (thickness != style.GetThickness())
		{
			thickness = std::nullopt;
		}
	});

	return thickness;
}

void CGroupOutlineStyle::SetThickness(double thickness)
{
	m_enumerator([thickness](IOutlineStyle& style) {
		style.SetThickness(thickness);
	});
}
