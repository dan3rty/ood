#pragma once

#include <ios>
#include <memory>

class IInputDataStream
{
public:
	[[nodiscard]] virtual bool IsEOF() const = 0;
	virtual std::uint8_t ReadByte() = 0;
	virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

	virtual ~IInputDataStream() = default;
};

using IInputDataStreamPtr = std::unique_ptr<IInputDataStream>;
