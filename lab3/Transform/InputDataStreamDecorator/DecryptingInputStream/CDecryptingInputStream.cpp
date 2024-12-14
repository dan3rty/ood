#include "CDecryptingInputStream.h"
#include "../../EncryptionTableBuilder/CEncryptionTableBuilder.h"

CDecryptingInputStream::CDecryptingInputStream(IInputDataStreamPtr&& stream, const int key)
	: CInputDataStreamDecorator(std::move(stream))
	, m_decryptionTable(CEncryptionTableBuilder::BuildDecryptionTable(key))
{
}

uint8_t CDecryptingInputStream::ReadByte()
{
	return DecryptByte(m_stream->ReadByte());
}

std::streamsize CDecryptingInputStream::ReadBlock(void* dstBuffer, const std::streamsize size)
{
	const auto readSize = m_stream->ReadBlock(dstBuffer, size);
	const auto bytes = static_cast<std::uint8_t*>(dstBuffer);

	for (std::streamsize i = 0; i < readSize; ++i)
	{
		*(bytes + i) = DecryptByte(*(bytes + i));
	}

	return readSize;
}

std::uint8_t CDecryptingInputStream::DecryptByte(const std::uint8_t byte) const
{
	return m_decryptionTable[static_cast<std::size_t>(byte)];
}
