#include "Canvas/CCanvas.h"
#include "Designer/CDesigner.h"
#include "Painter/CPainter.h"
#include "ShapeFactory/CShapeFactory.h"
#include <fstream>
#include <iostream>

int main()
{
	CShapeFactory shapeFactory;
	std::unique_ptr<IDesigner> designer = std::make_unique<CDesigner>(shapeFactory);

	std::ofstream output("output.svg");
	if (!output.is_open())
	{
		std::cerr << "Failed to create the picture" << std::endl;
		return EXIT_FAILURE;
	}

	CCanvas canvas(output);

	auto const pictureDraft = designer->CreateDraft(std::cin, std::cerr);
	CPainter::DrawPicture(pictureDraft, canvas);

	return EXIT_SUCCESS;
}
