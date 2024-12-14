#pragma once

#include "../../../Styles/IOutlineStyle.h"
#include "../CGroupStyleImpl.h"
#include <functional>

using OutlineStyleCallback = std::function<void(IOutlineStyle&)>;
using OutlineStyleEnumerator = std::function<void(OutlineStyleCallback const&)>;

class CGroupOutlineStyle final : public CGroupStyleImpl<IOutlineStyle, OutlineStyleEnumerator>
{
public:
	explicit CGroupOutlineStyle(OutlineStyleEnumerator&& enumerator);

	[[nodiscard]] std::optional<double> GetThickness() const override;
	void SetThickness(double thickness) override;
};
