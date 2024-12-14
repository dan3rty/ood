#include "CDocument.h"
#include "../Command/ChangeDocumentTitleCommand/CChangeDocumentTitleCommand.h"
#include "../Command/DeleteItemCommand/CDeleteItemCommand.h"
#include "../Command/InsertDocumentItemCommand/CInsertDocumentItemCommand.h"
#include "../Image/CImage.h"
#include "../Paragraph/CParagraph.h"

CDocument::CDocument(IHistory& history, ISaver& saver)
	: m_history(history)
	, m_saver(saver)
{
}

void CDocument::InsertParagraph(std::string const& text, std::optional<std::size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(text, m_history);
	auto item = std::make_shared<CDocumentItem>(std::move(paragraph));

	m_history.AddAndExecuteCommand(std::make_unique<CInsertDocumentItemCommand>(m_items, std::move(item), position));
}

void CDocument::InsertImage(std::string const& path, int width, int height, std::optional<std::size_t> position)
{
	auto image = std::make_shared<CImage>(path, width, height, m_history);
	auto item = std::make_shared<CDocumentItem>(std::move(image));

	m_history.AddAndExecuteCommand(std::make_unique<CInsertDocumentItemCommand>(m_items, std::move(item), position));
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem CDocument::GetItem(std::size_t index) const
{
	return static_cast<CConstDocumentItem>(m_items.at(index));
}

CDocumentItem CDocument::GetItem(std::size_t index)
{
	return m_items.at(index);
}

void CDocument::DeleteItem(std::size_t index)
{
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteItemCommand>(m_items, index));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

void CDocument::SetTitle(std::string const& title)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeDocumentTitleCommand>(m_title, title));
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

void CDocument::Save(std::string const& path) const
{
	m_saver.Save(*this, path);
}
