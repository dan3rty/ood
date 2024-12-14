#include "CMemoryOutputStream.h"

CMemoryOutputStream::CMemoryOutputStream(std::vector<std::uint8_t>& data)
	: m_data(data)
{
}

void CMemoryOutputStream::WriteByte(const std::uint8_t data)
{
	m_data.push_back(data);
}

void CMemoryOutputStream::WriteBlock(const void* srcData, const std::streamsize size)
{
	auto bytes = static_cast<std::uint8_t const*>(srcData);

	for (std::streamsize i = 0; i < size; ++i)
	{
		WriteByte(*(bytes++));
	}
}
