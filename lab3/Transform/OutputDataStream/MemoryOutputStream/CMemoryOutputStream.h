#pragma once

#include "../IOutputDataStream.h"
#include <vector>

class CMemoryOutputStream final : public IOutputDataStream
{
public:
	explicit CMemoryOutputStream(std::vector<std::uint8_t>& data);

	void WriteByte(std::uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::vector<std::uint8_t>& m_data;
};
