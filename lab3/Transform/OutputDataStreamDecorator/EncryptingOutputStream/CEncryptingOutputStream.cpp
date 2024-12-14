#include "CEncryptingOutputStream.h"
#include "../../EncryptionTableBuilder/CEncryptionTableBuilder.h"

CEncryptingOutputStream::CEncryptingOutputStream(IOutputDataStreamPtr&& stream, const int key)
	: m_stream(std::move(stream))
	, m_encryptionTable(CEncryptionTableBuilder::BuildEncryptionTable(key))
{
}

void CEncryptingOutputStream::WriteByte(const std::uint8_t data)
{
	m_stream->WriteByte(EncryptByte(data));
}

void CEncryptingOutputStream::WriteBlock(void const* srcData, const std::streamsize size)
{
	const auto bytes = static_cast<std::uint8_t const*>(srcData);

	for (std::streamsize i = 0; i < size; ++i)
	{
		WriteByte(*(bytes + i));
	}
}

std::uint8_t CEncryptingOutputStream::EncryptByte(const std::uint8_t byte) const
{
	return m_encryptionTable[static_cast<std::size_t>(byte)];
}
