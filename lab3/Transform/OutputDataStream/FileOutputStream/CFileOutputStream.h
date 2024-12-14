#pragma once

#include "../IOutputDataStream.h"
#include <fstream>

class CFileOutputStream final : public IOutputDataStream
{
public:
	explicit CFileOutputStream(std::string const& filename);

	void WriteByte(std::uint8_t data) override;
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ofstream m_file;
};
