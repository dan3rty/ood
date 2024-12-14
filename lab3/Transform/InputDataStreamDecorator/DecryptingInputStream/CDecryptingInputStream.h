#pragma once

#include "../../InputDataStream/IInputDataStream.h"
#include "../CInputDataStreamDecorator.h"
#include <memory>
#include <vector>

class CDecryptingInputStream final : public CInputDataStreamDecorator
{
public:
	explicit CDecryptingInputStream(IInputDataStreamPtr&& stream, int key);

	uint8_t ReadByte() override;
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	[[nodiscard]] std::uint8_t DecryptByte(std::uint8_t byte) const;

	std::vector<std::uint8_t> m_decryptionTable;
};
