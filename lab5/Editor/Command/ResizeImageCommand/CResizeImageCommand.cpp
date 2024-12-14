#include "CResizeImageCommand.h"
#include "../../Image/CImage.h"

CResizeImageCommand::CResizeImageCommand(int& imageWidth, int& imageHeight, int newWidth, int newHeight)
	: m_imageWidth(imageWidth)
	, m_imageHeight(imageHeight)
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
{
}

void CResizeImageCommand::DoExecute()
{
	std::swap(m_imageWidth, m_newWidth);
	std::swap(m_imageHeight, m_newHeight);
}

void CResizeImageCommand::DoRollback()
{
	std::swap(m_imageWidth, m_newWidth);
	std::swap(m_imageHeight, m_newHeight);
}
