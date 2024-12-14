#include "CSetParagraphTextCommand.h"

#include <utility>

CSetParagraphTextCommand::CSetParagraphTextCommand(std::string& paragraphText, std::string newText)
	: m_paragraphText(paragraphText)
	, m_newText(std::move(newText))
{
}

void CSetParagraphTextCommand::DoExecute()
{
	std::swap(m_paragraphText, m_newText);
}

void CSetParagraphTextCommand::DoRollback()
{
	std::swap(m_paragraphText, m_newText);
}
