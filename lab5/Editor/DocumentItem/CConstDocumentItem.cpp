#include "CConstDocumentItem.h"

CConstDocumentItem::CConstDocumentItem(std::shared_ptr<IImage>&& image)
	: m_image(std::move(image))
{
}

CConstDocumentItem::CConstDocumentItem(std::shared_ptr<IParagraph>&& paragraph)
	: m_paragraph(std::move(paragraph))
{
}

std::shared_ptr<IImage const> CConstDocumentItem::GetImage() const
{
	return m_image;
}

std::shared_ptr<IParagraph const> CConstDocumentItem::GetParagraph() const
{
	return m_paragraph;
}
