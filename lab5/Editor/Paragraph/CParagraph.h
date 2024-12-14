#pragma once

#include "../Document/ICommandExecutor.h"
#include "../DocumentItem/IParagraph.h"

class CParagraph final : public IParagraph
{
public:
	CParagraph(std::string text, ICommandExecutor& commandExecutor);

	[[nodiscard]] std::string GetText() const override;

	void SetText(std::string const& text) override;

private:
	std::string m_text;
	ICommandExecutor& m_commandExecutor;
};
