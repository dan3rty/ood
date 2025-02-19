#pragma once

#include <string>

class IParagraph
{
public:
	[[nodiscard]] virtual std::string GetText() const = 0;
	virtual void SetText(std::string const& text) = 0;

	virtual ~IParagraph() = default;
};
