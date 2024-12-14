#include "CEncryptionTableBuilder.h"
#include <random>

CEncryptionTableBuilder::Table CEncryptionTableBuilder::BuildEncryptionTable(const int key)
{
	Table encryptionTable(256);
	for (std::size_t i = 0; i <= 255; ++i)
	{
		encryptionTable[i] = static_cast<std::uint8_t>(i);
	}

	std::shuffle(encryptionTable.begin(), encryptionTable.end(), std::mt19937(key));

	return encryptionTable;
}

CEncryptionTableBuilder::Table CEncryptionTableBuilder::BuildDecryptionTable(const int key)
{
	auto const encryptionTable = BuildEncryptionTable(key);

	Table decryptionTable(256);
	for (std::size_t i = 0; i <= 255; ++i)
	{
		decryptionTable[static_cast<std::size_t>(encryptionTable[i])] = static_cast<std::uint8_t>(i);
	}

	return decryptionTable;
}
