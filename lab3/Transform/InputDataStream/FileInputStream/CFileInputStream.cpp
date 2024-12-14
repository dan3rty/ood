#include "CFileInputStream.h"

CFileInputStream::CFileInputStream(const std::string& filename)
	: m_file(filename, std::ios_base::in | std::ios_base::binary)
{
	m_file.unsetf(std::ios_base::skipws);
	if (!m_file.is_open())
	{
		throw std::runtime_error("failed to open file for reading");
	}
}

bool CFileInputStream::IsEOF() const
{
	m_file.peek(); // Peeking to set EOF flag
	return m_file.eof();
}

uint8_t CFileInputStream::ReadByte()
{
	if (IsEOF())
	{
		throw std::ios_base::failure("failed to read from file");
	}

	const std::uint8_t byte = m_file.get();

	if (m_file.bad())
	{
		throw std::ios_base::failure("failed to read from file");
	}

	return byte;
}

std::streamsize CFileInputStream::ReadBlock(void* dstBuffer, std::streamsize size)
{
	m_file.read(static_cast<char*>(dstBuffer), size);

	if (m_file.bad())
	{
		throw std::ios_base::failure("failed to read from file");
	}

	return m_file.gcount();
}
