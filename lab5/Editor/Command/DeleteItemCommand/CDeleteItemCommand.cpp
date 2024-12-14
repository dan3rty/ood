#include "CDeleteItemCommand.h"

CDeleteItemCommand::CDeleteItemCommand(std::vector<CDocumentItem>& items, std::size_t index)
	: m_items(items)
	, m_index(index)
{
	if (m_index >= items.size())
	{
		throw std::invalid_argument("invalid index");
	}

	m_deletedItem = std::make_unique<CDocumentItem>(m_items.at(index));
}

void CDeleteItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + static_cast<int>(m_index));
}

void CDeleteItemCommand::DoRollback()
{
	m_items.emplace(m_items.begin() + static_cast<int>(m_index), *m_deletedItem);
}
