#pragma once

#include "../Document/ISaver.h"
#include <unordered_map>

class CHtmlSaver final : public ISaver
{
public:
	void Save(IDocument const& document, std::string const& path) override;

private:
	static constexpr std::string_view IMAGES_DIRECTORY = "html_images";
	static inline std::unordered_map<char, std::string> const ESCAPE_SEQUENCES = {
		{ '&', "&amp;" },
		{ '<', "&lt;" },
		{ '>', "&gt;" },
		{ '"', "&quot;" },
		{ '\'', "&apos;" },
	};

	static std::string CreateImagesDirectory(std::string const& documentPath);
	static std::string GetImagesDirectoryPath(std::string const& documentPath);

	static void WriteHeader(std::ostream& output, IDocument const& document);
	static void WriteImage(std::ostream& output, std::shared_ptr<IImage const> const& image, std::string const& imagesDirectoryPath);
	static void WriteParagraph(std::ostream& output, std::shared_ptr<IParagraph const> const& paragraph);
	static void WriteFooter(std::ofstream& output);

	static std::string Escape(std::string const& result);
};
