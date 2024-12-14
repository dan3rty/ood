#include "CHtmlSaver.h"
#include <filesystem>
#include <fstream>
#include <numeric>

namespace fs = std::filesystem;

void CHtmlSaver::Save(IDocument const& document, std::string const& path)
{
	std::ofstream output(path);
	auto const imagesDirectoryPath = CreateImagesDirectory(path);

	WriteHeader(output, document);

	for (std::size_t i = 0; i < document.GetItemsCount(); ++i)
	{
		auto item = document.GetItem(i);

		if (auto const& image = item.GetImage())
		{
			WriteImage(output, image, imagesDirectoryPath);
		}
		else if (auto const& paragraph = item.GetParagraph())
		{
			WriteParagraph(output, paragraph);
		}
	}

	WriteFooter(output);
}

// Title тож экранировать бы (да вообще всё!!!)
void CHtmlSaver::WriteHeader(std::ostream& output, IDocument const& document)
{
	output << "<html>" << std::endl
		   << "<head>" << std::endl
		   << "  <title>" << Escape(document.GetTitle()) << "</title>" << std::endl
		   << "</head>" << std::endl
		   << "<body>" << std::endl;
}

void CHtmlSaver::WriteImage(std::ostream& output, std::shared_ptr<IImage const> const& image, std::string const& imagesDirectoryPath)
{
	auto imageDestinationPath = fs::path(imagesDirectoryPath) / fs::path(image->GetPath()).filename();
	fs::copy(
		image->GetPath(),
		imageDestinationPath,
		fs::copy_options::overwrite_existing);

	output << "  <img src=\"" << Escape(imageDestinationPath.string()) << "\" "
		   << "width=\"" << image->GetWidth() << "\" "
		   << "height=\"" << image->GetHeight() << "\" />" << std::endl;
}

void CHtmlSaver::WriteParagraph(std::ostream& output, std::shared_ptr<IParagraph const> const& paragraph)
{
	output << "  <p>" << Escape(paragraph->GetText()) << "</p>" << std::endl;
}

void CHtmlSaver::WriteFooter(std::ofstream& output)
{
	output << "</body>" << std::endl
		   << "</html>" << std::endl;
}

std::string CHtmlSaver::CreateImagesDirectory(std::string const& documentPath)
{
	auto imagesDirectoryPath = GetImagesDirectoryPath(documentPath);
	if (!fs::is_directory(imagesDirectoryPath))
	{
		fs::create_directory(imagesDirectoryPath);
	}

	return imagesDirectoryPath;
}

std::string CHtmlSaver::GetImagesDirectoryPath(std::string const& documentPath)
{
	auto const documentRootPath = fs::path(documentPath).parent_path();
	auto const destinationPath = documentRootPath / IMAGES_DIRECTORY;

	return destinationPath.string();
}

std::string CHtmlSaver::Escape(std::string const& str)
{
	return std::accumulate(
		str.begin(),
		str.end(),
		std::string(),
		[](auto const result, auto const ch) {
			auto const escaped = ESCAPE_SEQUENCES.find(ch);
			if (escaped != ESCAPE_SEQUENCES.end())
			{
				return result + escaped->second;
			}
			return result + ch;
		});
}
