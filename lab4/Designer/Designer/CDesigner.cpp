#include "CDesigner.h"
#include <iostream>

CDesigner::CDesigner(IShapeFactory& shapeFactory)
	: m_shapeFactory(shapeFactory)
{
}

CPictureDraft CDesigner::CreateDraft(std::istream& stream, std::ostream& outStream)
{
	CPictureDraft draft;
	std::string description;

	while (std::getline(stream, description))
	{
		if (description.empty() || description.starts_with(COMMENT_CHARACTER))
		{
			continue;
		}

		if (description == "end")
		{
			break;
		}

		try
		{
			draft.AddShape(m_shapeFactory.CreateShape(description));
		}
		catch (std::exception const& e)
		{
			outStream << "Error: " << e.what() << "\n  Skipping '" << description << "' shape" << std::endl;
		}
	}

	return draft;
}
