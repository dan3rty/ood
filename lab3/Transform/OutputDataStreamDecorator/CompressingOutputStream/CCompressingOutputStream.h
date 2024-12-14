#pragma once

#include "../../OutputDataStream/IOutputDataStream.h"

struct Block
{
	std::uint8_t byte = 0;
	std::uint8_t size = 0;
};

class CCompressingOutputStream final : public IOutputDataStream
{
public:
	explicit CCompressingOutputStream(IOutputDataStreamPtr&& stream);

	~CCompressingOutputStream() override;

	void WriteByte(std::uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	void Flush() const;

	Block m_currentBlock;
	IOutputDataStreamPtr m_stream;
};
