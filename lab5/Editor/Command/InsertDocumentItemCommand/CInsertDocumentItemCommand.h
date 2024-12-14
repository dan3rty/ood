#pragma once

#include "../../DocumentItem/CDocumentItem.h"
#include "../AbstractCommand/CAbstractCommand.h"
#include <optional>
#include <vector>

class CInsertDocumentItemCommand final : public CAbstractCommand
{
public:
	CInsertDocumentItemCommand(std::vector<CDocumentItem>& items, std::shared_ptr<CDocumentItem>&& newItem, std::optional<std::size_t> index);

private:
	void DoExecute() override;
	void DoRollback() override;

	std::vector<CDocumentItem>& m_items;
	std::shared_ptr<CDocumentItem> m_newItem;
	std::optional<std::size_t> m_index;
};
