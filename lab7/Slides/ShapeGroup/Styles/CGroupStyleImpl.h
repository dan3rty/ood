#pragma once

#include "../../Shapes/ShapeTypes.h"
#include <optional>

template <class Base, typename Enumerator>
class CGroupStyleImpl : public Base
{
public:
	explicit CGroupStyleImpl(Enumerator&& enumerator)
		: m_enumerator(std::move(enumerator))
	{
	}

	[[nodiscard]] std::optional<bool> IsEnabled() const final
	{
		std::optional<bool> enabled;
		bool sequential = false;

		m_enumerator([&enabled, &sequential](Base& style) {
			if (!sequential)
			{
				enabled = style.IsEnabled();
				sequential = true;
			}

			if (enabled != style.IsEnabled())
			{
				enabled = std::nullopt;
			}
		});

		return enabled;
	}

	void Enable() final
	{
		m_enumerator([](Base& style) {
			style.Enable();
		});
	}

	void Disable() final
	{
		m_enumerator([](Base& style) {
			style.Disable();
		});
	}

	[[nodiscard]] std::optional<RgbaColor> GetColor() const final
	{
		std::optional<RgbaColor> color;
		bool sequential = false;

		m_enumerator([&color, &sequential](Base& style) {
			if (!sequential)
			{
				color = style.GetColor();
				sequential = true;
			}

			if (color != style.GetColor())
			{
				color = std::nullopt;
			}
		});

		return color;
	}

	void SetColor(RgbaColor color) final
	{
		m_enumerator([color](Base& style) {
			style.SetColor(color);
		});
	}

protected:
	Enumerator m_enumerator;
};
