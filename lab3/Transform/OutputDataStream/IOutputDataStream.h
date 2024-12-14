#pragma once

#include <ios>
#include <memory>

class IOutputDataStream
{
public:
	virtual void WriteByte(std::uint8_t data) = 0;
	virtual void WriteBlock(void const* srcData, std::streamsize size) = 0;

	virtual ~IOutputDataStream() = default;
};

using IOutputDataStreamPtr = std::unique_ptr<IOutputDataStream>;
