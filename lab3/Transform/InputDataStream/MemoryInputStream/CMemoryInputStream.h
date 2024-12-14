#pragma once

#include "../IInputDataStream.h"
#include <vector>

class CMemoryInputStream final : public IInputDataStream
{
public:
	explicit CMemoryInputStream(std::vector<std::uint8_t>& data);

	[[nodiscard]] bool IsEOF() const override;
	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	std::vector<std::uint8_t>& m_data;
	std::size_t m_currentPosition = 0;
};
