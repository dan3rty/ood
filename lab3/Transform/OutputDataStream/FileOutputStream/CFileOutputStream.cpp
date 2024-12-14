#include "CFileOutputStream.h"

CFileOutputStream::CFileOutputStream(std::string const& filename)
	: m_file(filename, std::ios::out | std::ios::binary)
{
	if (!m_file.is_open())
	{
		throw std::runtime_error("failed to open file for writing");
	}
}

void CFileOutputStream::WriteByte(const std::uint8_t data)
{
	WriteBlock(&data, 1);
}

void CFileOutputStream::WriteBlock(void const* srcData, const std::streamsize size)
{
	m_file.write(static_cast<char const*>(srcData), size);

	if (m_file.bad())
	{
		throw std::ios_base::failure("failed to write to file");
	}

	m_file.flush();
}
