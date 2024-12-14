#pragma once

#include "CConstDocumentItem.h"
#include <memory>

class CDocumentItem final : public CConstDocumentItem
{
public:
	explicit CDocumentItem(std::shared_ptr<IImage>&& image);
	explicit CDocumentItem(std::shared_ptr<IParagraph>&& paragraph);

	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<IParagraph> GetParagraph();
};
