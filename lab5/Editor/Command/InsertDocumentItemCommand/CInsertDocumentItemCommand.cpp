#include "CInsertDocumentItemCommand.h"

CInsertDocumentItemCommand::CInsertDocumentItemCommand(std::vector<CDocumentItem>& items, std::shared_ptr<CDocumentItem>&& newItem, std::optional<std::size_t> index)
	: m_items(items)
	, m_newItem(std::move(newItem))
	, m_index(index)
{
	if (m_index.has_value() && m_index.value() > items.size())
	{
		throw std::invalid_argument("invalid index");
	}
}

void CInsertDocumentItemCommand::DoExecute()
{
	if (m_index.has_value())
	{
		m_items.emplace(m_items.begin() + static_cast<int>(m_index.value()), *m_newItem);
		return;
	}

	m_items.push_back(*m_newItem);
}

void CInsertDocumentItemCommand::DoRollback()
{
	if (m_index.has_value())
	{
		m_items.erase(m_items.begin() + static_cast<int>(m_index.value()));
		return;
	}

	// при комменте этой штуки тесты прошли
	m_items.pop_back();
}
