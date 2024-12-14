#include "CArgumentParser.h"
#include <charconv>
#include <stdexcept>

CArgumentParser::CArgumentParser(const int argc, char const** argv)
	: m_args(argv + 1, argv + argc)
{
}

Args CArgumentParser::Parse() const
{
	Args args;

	for (auto it = m_args.begin(); it != m_args.end(); ++it)
	{
		if (*it == ENCRYPT_PARAMETER && ++it != m_args.end())
		{
			args.encryptionKeys.push_back(StringViewToInt(*it));
			continue;
		}

		if (*it == DECRYPT_PARAMETER && ++it != m_args.end())
		{
			args.decryptionKeys.insert(args.decryptionKeys.begin(), StringViewToInt(*it));
			continue;
		}

		if (*it == COMPRESS_PARAMETER)
		{
			args.compress = true;
			continue;
		}

		if (*it == DECOMPRESS_PARAMETER)
		{
			args.decompress = true;
			continue;
		}

		if (args.inputFilename.empty())
		{
			args.inputFilename = *it;
			continue;
		}
		if (args.outputFilename.empty())
		{
			args.outputFilename = *it;
			continue;
		}

		throw std::invalid_argument("unsupported option: " + std::string(*it));
	}

	if (args.outputFilename.empty())
	{
		throw std::invalid_argument("output file not specified");
	}

	if (args.inputFilename.empty())
	{
		throw std::invalid_argument("input file not specified");
	}

	return args;
}

int CArgumentParser::StringViewToInt(std::string_view const& view)
{
	int value;
	auto result = std::from_chars(view.data(), view.data() + view.size(), value);

	if (result.ec == std::errc::invalid_argument)
	{
		throw std::invalid_argument("invalid number value: " + std::string(view));
	}
	if (result.ec == std::errc::result_out_of_range)
	{
		throw std::out_of_range("number out of range: " + std::string(view));
	}

	return value;
}
