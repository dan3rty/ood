#include "CDecompressingInputStream.h"

CDecompressingInputStream::CDecompressingInputStream(IInputDataStreamPtr&& stream)
	: CInputDataStreamDecorator(std::move(stream))
{
}

uint8_t CDecompressingInputStream::ReadByte()
{
	if (m_currentBlock.size == 0)
	{
		m_currentBlock.size = m_stream->ReadByte();
		m_currentBlock.byte = m_stream->ReadByte();
	}

	--m_currentBlock.size;
	return m_currentBlock.byte;
}

std::streamsize CDecompressingInputStream::ReadBlock(void* dstBuffer, const std::streamsize size)
{
	const auto bytes = static_cast<std::uint8_t*>(dstBuffer);

	std::streamsize i;
	for (i = 0; i < size && !IsEOF(); ++i)
	{
		*(bytes + i) = ReadByte();
	}

	return i + 1;
}
