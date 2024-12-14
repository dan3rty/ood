#pragma once

#include "../Document/ICommandExecutor.h"
#include "../DocumentItem/IImage.h"
#include <set>

class CImage final : public IImage
{
public:
	CImage(std::string const& path, int width, int height, ICommandExecutor& commandExecutor);

	~CImage() noexcept override;

	[[nodiscard]] std::string GetPath() const override;

	[[nodiscard]] int GetWidth() const override;
	[[nodiscard]] int GetHeight() const override;

	void Resize(int width, int height) override;

private:
	static constexpr int MIN_WIDTH = 1;
	static constexpr int MAX_WIDTH = 5000;

	static constexpr int MIN_HEIGHT = 1;
	static constexpr int MAX_HEIGHT = 5000;

	static inline std::set<std::string> const IMAGE_EXTENSIONS = { ".jpg", ".png", ".svg", ".gif" };

	static inline std::string const BASE_FILENAME = "image_";

	static void ValidateDimensions(int width, int height);
	static void ValidateImageFormat(std::string const& path);
	static void ValidateFileExists(std::string const& path);

	static std::string GetNextFilename();

	static std::size_t m_nextImageId;

	std::string m_path;
	int m_width;
	int m_height;
	ICommandExecutor& m_commandExecutor;
};
