#pragma once

#include "../Common/App/IDrawable.h"
#include "../Styles/IOutlineStyle.h"
#include <memory>

class IShapeGroup;

class IShape : public IDrawable
{
public:
	[[nodiscard]] virtual std::optional<RectD> GetFrame() const = 0;
	virtual void SetFrame(RectD const& rect) = 0;

	virtual std::shared_ptr<IOutlineStyle> GetOutlineStyle() = 0;
	[[nodiscard]] virtual std::shared_ptr<IOutlineStyle const> GetOutlineStyle() const = 0;

	virtual std::shared_ptr<IStyle> GetFillStyle() = 0;
	[[nodiscard]] virtual std::shared_ptr<IStyle const> GetFillStyle() const = 0;

	virtual std::shared_ptr<IShapeGroup> GetGroup() = 0;
	[[nodiscard]] virtual std::shared_ptr<IShapeGroup const> GetGroup() const = 0;
};
