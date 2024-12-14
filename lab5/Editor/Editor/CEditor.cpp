#include "CEditor.h"
#include <sstream>

static void TrimString(std::string& str)
{
	str.erase(0, str.find_first_not_of(' '));
	str.erase(str.find_last_not_of(' ') + 1);
}

CEditor::CEditor(std::istream& input, std::ostream& output, IHistory& history, ISaver& saver)
	: m_document(history, saver)
	, m_input(input)
	, m_output(output)
{
}

void CEditor::Start()
{
	std::string argsString;

	while (m_running && (m_output << "> ") && std::getline(m_input, argsString))
	{
		std::istringstream args(argsString);
		std::string commandName;

		args >> commandName;

		try
		{
			auto const handler = GetCommandHandler(commandName);
			handler(args);
		}
		catch (std::exception const& e)
		{
			m_output << "Error: " << e.what() << std::endl;
		}
	}

	m_output << "Bye" << std::endl;
}

CEditor::CommandHandler CEditor::GetCommandHandler(std::string const& commandName)
{
	if (commandName == "InsertParagraph")
	{
		return [this](std::istream& input) {
			InsertParagraph(input);
		};
	}
	if (commandName == "InsertImage")
	{
		return [this](std::istream& input) {
			InsertImage(input);
		};
	}
	if (commandName == "SetTitle")
	{
		return [this](std::istream& input) {
			SetTitle(input);
		};
	}
	if (commandName == "List")
	{
		return [this](std::istream& /* input */) {
			List();
		};
	}
	if (commandName == "ReplaceText")
	{
		return [this](std::istream& input) {
			ReplaceText(input);
		};
	}
	if (commandName == "ResizeImage")
	{
		return [this](std::istream& input) {
			ResizeImage(input);
		};
	}
	if (commandName == "DeleteItem")
	{
		return [this](std::istream& input) {
			DeleteItem(input);
		};
	}
	if (commandName == "Help")
	{
		return [this](std::istream& /* input */) {
			Help();
		};
	}
	if (commandName == "Undo")
	{
		return [this](std::istream& /* input */) {
			Undo();
		};
	}
	if (commandName == "Redo")
	{
		return [this](std::istream& /* input */) {
			Redo();
		};
	}
	if (commandName == "Save")
	{
		return [this](std::istream& input) {
			Save(input);
		};
	}
	if (commandName == "Exit")
	{
		return [this](std::istream& /* input */) {
			Exit();
		};
	}

	throw std::runtime_error("unknown command: " + commandName);
}

void CEditor::InsertParagraph(std::istream& input)
{
	std::string index;
	std::string text;

	if (!(input >> index) || !std::getline(input, text))
	{
		throw std::invalid_argument("invalid parameters for InsertParagraph");
	}

	TrimString(text);
	m_document.InsertParagraph(text, GetOptionalIndex(index));
}

void CEditor::InsertImage(std::istream& input)
{
	std::string index;
	int width;
	int height;
	std::string path;

	if (!(input >> index >> width >> height) || !std::getline(input, path))
	{
		throw std::invalid_argument("invalid parameters for InsertImage");
	}

	TrimString(path);
	m_document.InsertImage(path, width, height, GetOptionalIndex(index));
}

void CEditor::SetTitle(std::istream& input)
{
	std::string title;

	if (!std::getline(input, title))
	{
		throw std::invalid_argument("invalid parameters for SetTitle");
	}

	TrimString(title);
	m_document.SetTitle(title);
}

void CEditor::List()
{
	m_output << "Title: " << m_document.GetTitle() << std::endl;
	for (std::size_t i = 0; i < m_document.GetItemsCount(); ++i)
	{
		m_output << std::to_string(i) << ". ";
		auto item = m_document.GetItem(i);

		if (auto const& image = item.GetImage())
		{
			m_output << "Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath();
		}
		else if (auto const& paragraph = item.GetParagraph())
		{
			m_output << "Paragraph: " << paragraph->GetText();
		}

		m_output << std::endl;
	}
}

void CEditor::ReplaceText(std::istream& input)
{
	std::size_t index;
	std::string text;

	if (!(input >> index) || !std::getline(input, text))
	{
		throw std::invalid_argument("invalid parameters for ReplaceText");
	}

	auto const& paragraph = m_document.GetItem(index).GetParagraph();
	if (!paragraph)
	{
		throw std::runtime_error("element is not a paragraph");
	}

	TrimString(text);
	paragraph->SetText(text);
}

void CEditor::ResizeImage(std::istream& input)
{
	std::size_t index;
	int width;
	int height;

	if (!(input >> index >> width >> height))
	{
		throw std::invalid_argument("invalid parameters for ResizeImage");
	}

	auto const& image = m_document.GetItem(index).GetImage();
	if (!image)
	{
		throw std::runtime_error("element is not a image");
	}

	image->Resize(width, height);
}

void CEditor::DeleteItem(std::istream& input)
{
	std::size_t index;

	if (!(input >> index))
	{
		throw std::invalid_argument("invalid parameters for DeleteItem");
	}

	m_document.DeleteItem(index);
}

void CEditor::Help()
{
	m_output << "Available commands:" << std::endl
			 << "InsertParagraph <index>|end <text>" << std::endl
			 << "InsertImage <index>|end <width> <height> <image path>" << std::endl
			 << "SetTitle <title>" << std::endl
			 << "List" << std::endl
			 << "ReplaceText <index> <text>" << std::endl
			 << "ResizeImage <index> <width> <height>" << std::endl
			 << "DeleteItem <index>" << std::endl
			 << "Help" << std::endl
			 << "Undo" << std::endl
			 << "Redo" << std::endl
			 << "Save <path>" << std::endl
			 << "Exit"
			 << std::endl;
}

void CEditor::Undo()
{
	if (!m_document.CanUndo())
	{
		throw std::runtime_error("can not undo");
	}

	m_document.Undo();
}

void CEditor::Redo()
{
	if (!m_document.CanRedo())
	{
		throw std::runtime_error("can not redo");
	}

	m_document.Redo();
}

void CEditor::Save(std::istream& input)
{
	std::string path;

	if (!std::getline(input, path))
	{
		throw std::invalid_argument("invalid parameters for Save");
	}

	TrimString(path);
	m_document.Save(path);
}

void CEditor::Exit()
{
	m_running = false;
}

std::optional<std::size_t> CEditor::GetOptionalIndex(std::string const& value)
{
	if (value != "end")
	{
		return static_cast<std::size_t>(std::stoi(value));
	}

	return std::nullopt;
}
