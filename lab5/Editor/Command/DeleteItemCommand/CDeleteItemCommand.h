#pragma once

#include "../../DocumentItem/CDocumentItem.h"
#include "../AbstractCommand/CAbstractCommand.h"
#include <vector>

class CDeleteItemCommand final : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<CDocumentItem>& items, std::size_t index);

private:
	void DoExecute() override;
	void DoRollback() override;

	std::vector<CDocumentItem>& m_items;
	std::size_t m_index;
	std::unique_ptr<CDocumentItem> m_deletedItem;
};
