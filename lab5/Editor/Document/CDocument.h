#pragma once

#include "../Editor/IDocument.h"
#include "IHistory.h"
#include "ISaver.h"
#include <vector>

class CDocument final : public IDocument
{
public:
	explicit CDocument(IHistory& history, ISaver& saver);

	void InsertParagraph(std::string const& text, std::optional<std::size_t> position) override;
	void InsertImage(std::string const& path, int width, int height, std::optional<std::size_t> position) override;

	[[nodiscard]] size_t GetItemsCount() const override;

	[[nodiscard]] CConstDocumentItem GetItem(std::size_t index) const override;
	CDocumentItem GetItem(std::size_t index) override;

	void DeleteItem(std::size_t index) override;

	[[nodiscard]] std::string GetTitle() const override;
	void SetTitle(std::string const& title) override;

	[[nodiscard]] bool CanUndo() const override;
	void Undo() override;

	[[nodiscard]] bool CanRedo() const override;
	void Redo() override;

	void Save(std::string const& path) const override;

private:
	IHistory& m_history;
	ISaver& m_saver;

	std::vector<CDocumentItem> m_items;
	std::string m_title;
};
