#pragma once

#include <cstdint>
#include <vector>

class CEncryptionTableBuilder
{
public:
	using Table = std::vector<std::uint8_t>;

	static Table BuildEncryptionTable(int key);
	static Table BuildDecryptionTable(int key);
};
