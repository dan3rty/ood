#include "CDocumentItem.h"

CDocumentItem::CDocumentItem(std::shared_ptr<IImage>&& image)
	: CConstDocumentItem(std::move(image))
{
}

CDocumentItem::CDocumentItem(std::shared_ptr<IParagraph>&& paragraph)
	: CConstDocumentItem(std::move(paragraph))
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
