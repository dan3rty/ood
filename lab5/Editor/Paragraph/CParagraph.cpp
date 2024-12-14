#include "CParagraph.h"

#include <utility>
#include "../Command/SetParagraphTextCommand/CSetParagraphTextCommand.h"

CParagraph::CParagraph(std::string text, ICommandExecutor& commandExecutor)
	: m_text(std::move(text))
	, m_commandExecutor(commandExecutor)
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(std::string const& text)
{
	m_commandExecutor.AddAndExecuteCommand(std::make_unique<CSetParagraphTextCommand>(m_text, text));
}
