#include "CInputDataStreamDecorator.h"

bool CInputDataStreamDecorator::IsEOF() const
{
	return m_stream->IsEOF();
}

CInputDataStreamDecorator::CInputDataStreamDecorator(IInputDataStreamPtr&& stream)
	: m_stream(std::move(stream))
{
}
