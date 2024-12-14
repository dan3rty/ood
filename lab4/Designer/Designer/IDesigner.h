#pragma once

#include "../PictureDraft/CPictureDraft.h"

// либо убрать либо доказать зач он нужен
class IDesigner
{
public:
	virtual CPictureDraft CreateDraft(std::istream& stream, std::ostream& errorStream) = 0;

	virtual ~IDesigner() = default;
};
