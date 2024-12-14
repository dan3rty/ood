#pragma once

#include <string>
#include <vector>

struct Args
{
	std::string inputFilename;
	std::string outputFilename;

	std::vector<int> encryptionKeys;
	std::vector<int> decryptionKeys;

	bool compress = false;
	bool decompress = false;
};

class CArgumentParser
{
public:
	CArgumentParser(int argc, char const** argv);

	[[nodiscard]] Args Parse() const;

private:
	static int StringViewToInt(std::string_view const& view);

	static constexpr std::string_view ENCRYPT_PARAMETER = "--encrypt";
	static constexpr std::string_view DECRYPT_PARAMETER = "--decrypt";
	static constexpr std::string_view COMPRESS_PARAMETER = "--compress";
	static constexpr std::string_view DECOMPRESS_PARAMETER = "--decompress";

	std::vector<std::string_view> m_args;
};
