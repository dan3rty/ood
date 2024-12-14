#pragma once

#include "../AbstractCommand/CAbstractCommand.h"
#include <string>

class CSetParagraphTextCommand final : public CAbstractCommand
{
public:
	CSetParagraphTextCommand(std::string& paragraphText, std::string newText);

private:
	void DoExecute() override;
	void DoRollback() override;

	std::string& m_paragraphText;
	std::string m_newText;
};
