#include "CChangeDocumentTitleCommand.h"

#include <utility>

CChangeDocumentTitleCommand::CChangeDocumentTitleCommand(std::string& documentTitle, std::string  newTitle)
	: m_documentTitle(documentTitle)
	, m_newTitle(std::move(newTitle))
{
}

void CChangeDocumentTitleCommand::DoExecute()
{
	std::swap(m_documentTitle, m_newTitle);
}

void CChangeDocumentTitleCommand::DoRollback()
{
	std::swap(m_documentTitle, m_newTitle);
}
