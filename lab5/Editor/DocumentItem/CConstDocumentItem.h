#pragma once

#include "IImage.h"
#include "IParagraph.h"
#include <memory>

class CConstDocumentItem
{
public:
	explicit CConstDocumentItem(std::shared_ptr<IImage>&& image);
	explicit CConstDocumentItem(std::shared_ptr<IParagraph>&& paragraph);

	[[nodiscard]] std::shared_ptr<IImage const> GetImage() const;
	[[nodiscard]] std::shared_ptr<IParagraph const> GetParagraph() const;

	virtual ~CConstDocumentItem() = default;

protected:
	std::shared_ptr<IImage> m_image = nullptr;
	std::shared_ptr<IParagraph> m_paragraph = nullptr;
};
