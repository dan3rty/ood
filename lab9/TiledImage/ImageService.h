#pragma once
#include "Image.h"
#include <fstream>

class ImageService
{
public:
	static void Print(const Image& image, std::ostream& output);

	static Image LoadImage(const std::string& pixels);

	static void SaveImageToPPM(const Image& image, const std::string& filename);
};
