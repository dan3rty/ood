#include "CMemoryInputStream.h"

CMemoryInputStream::CMemoryInputStream(std::vector<std::uint8_t>& data)
	: m_data(data)
{
}

bool CMemoryInputStream::IsEOF() const
{
	return m_currentPosition == m_data.size();
}

uint8_t CMemoryInputStream::ReadByte()
{
	if (IsEOF())
	{
		throw std::ios_base::failure("can not read past EOF");
	}

	return m_data[m_currentPosition++];
}

std::streamsize CMemoryInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	auto bytes = static_cast<std::uint8_t*>(dstBuffer);
	const auto readSize = std::min(
		size,
		static_cast<std::streamsize>(m_data.size() - m_currentPosition));

	for (std::streamsize i = 0; i < readSize; ++i)
	{
		*(bytes++) = ReadByte();
	}

	return readSize;
}
