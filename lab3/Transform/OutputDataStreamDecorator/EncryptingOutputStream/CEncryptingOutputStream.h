#pragma once

#include "../../OutputDataStream/IOutputDataStream.h"
#include <memory>
#include <vector>

class CEncryptingOutputStream final : public IOutputDataStream
{
public:
	explicit CEncryptingOutputStream(IOutputDataStreamPtr&& stream, int key);

	void WriteByte(std::uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	[[nodiscard]] std::uint8_t EncryptByte(std::uint8_t byte) const;

	IOutputDataStreamPtr m_stream;
	std::vector<std::uint8_t> m_encryptionTable;
};
