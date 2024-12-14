#include "ImageService.h"
#include <fstream>
#include <sstream>

void ImageService::Print(const Image& image, std::ostream& output)
{
	const auto [width, height] = image.GetSize();
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			output.put(static_cast<char>(image.GetPixel({ x, y })));
		}
		output.put('\n');
	}
}

Image ImageService::LoadImage(const std::string& pixels)
{
	std::istringstream string(pixels);
	Size size{};
	std::string line;
	while (std::getline(string, line))
	{
		size.width = std::max(size.width, static_cast<int>(line.length()));
		++size.height;
	}

	Image img(size);

	string = std::istringstream(pixels);
	for (int y = 0; y < size.height; ++y)
	{
		if (!std::getline(string, line))
		{
			break;
		}

		int x = 0;
		for (const auto ch : line)
		{
			img.SetPixel({ x++, y }, ch);
		}
	}

	return img;
}

void ImageService::SaveImageToPPM(const Image& image, const std::string& filename)
{
	std::ofstream file(filename);
	if (!file.is_open())
	{
		throw std::runtime_error("Could not open the file for writing");
	}

	file << "P3\n";
	file << image.GetSize().width << " " << image.GetSize().height << "\n";
	file << "255\n";

	for (int y = 0; y < image.GetSize().height; ++y)
	{
		for (int x = 0; x < image.GetSize().width; ++x)
		{
			const uint32_t color = image.GetPixel({ x, y });

			const uint8_t r = (color >> 16) & 0xFF;
			const uint8_t g = (color >> 8) & 0xFF;
			const uint8_t b = color & 0xFF;

			file << static_cast<int>(r) << " "
				 << static_cast<int>(g) << " "
				 << static_cast<int>(b) << " ";
		}
		file << "\n";
	}

	file.close();
}
