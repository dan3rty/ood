#pragma once

#include "../Document/CDocument.h"
#include "../Document/IHistory.h"
#include "../Document/ISaver.h"
#include "IDocument.h"
#include <functional>
#include <iostream>

class CEditor
{
public:
	CEditor(std::istream& input, std::ostream& output, IHistory& history, ISaver& saver);

	void Start();

private:
	using CommandHandler = std::function<void(std::istream&)>;

	CommandHandler GetCommandHandler(std::string const& commandName);

	void InsertParagraph(std::istream& input);
	void InsertImage(std::istream& input);

	void SetTitle(std::istream& input);

	void List();

	void ReplaceText(std::istream& input);
	void ResizeImage(std::istream& input);

	void DeleteItem(std::istream& input);

	void Help();

	void Undo();
	void Redo();

	void Save(std::istream& input);

	void Exit();

	static std::optional<std::size_t> GetOptionalIndex(std::string const& value);

	std::istream& m_input;
	std::ostream& m_output;
	bool m_running = true;

	CDocument m_document;
};
