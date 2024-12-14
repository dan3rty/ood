#include "Common/Infrastructure/SVG/CCanvas.h"
#include "ShapeGroup/CShapeGroup.h"
#include "Shapes/Ellipse/CEllipse.h"
#include "Shapes/Rectangle/CRectangle.h"
#include "Shapes/Triangle/CTriangle.h"
#include "Slide/Slide/CSlide.h"
#include <fstream>

constexpr auto OUTPUT_FILENAME = "output.svg";

std::shared_ptr<IShape> CreateKurwa()
{
	const auto head = std::make_shared<CEllipse>(PointD{100, 100}, 80, 70);
	head->GetFillStyle()->SetColor(0x943c06);
	head->GetOutlineStyle()->SetColor(0x000000);
	head->GetOutlineStyle()->SetThickness(3);

	const auto nose = std::make_shared<CEllipse>(PointD{100, 120}, 20, 15);
	nose->GetFillStyle()->SetColor(0x000000);
	nose->GetOutlineStyle()->Disable();

	const auto leftEar = std::make_shared<CTriangle>(PointD{45, 50}, PointD{50, 20}, PointD{80, 50});
	leftEar->GetFillStyle()->SetColor(0x943c06);
	leftEar->GetOutlineStyle()->SetColor(0x000000);
	leftEar->GetOutlineStyle()->SetThickness(3);

	const auto rightEar = std::make_shared<CTriangle>(PointD{120, 50}, PointD{150, 20}, PointD{155, 50});
	rightEar->GetFillStyle()->SetColor(0x943c06);
	rightEar->GetOutlineStyle()->SetColor(0x000000);
	rightEar->GetOutlineStyle()->SetThickness(3);

	const auto leftTooth = std::make_shared<CRectangle>(PointD{89, 135}, 10, 20);
	leftTooth->GetFillStyle()->SetColor(0xffffff);
	leftTooth->GetOutlineStyle()->SetColor(0x000000);
	leftTooth->GetOutlineStyle()->SetThickness(1);

	const auto rightTooth = std::make_shared<CRectangle>(PointD{101, 135}, 10, 20);
	rightTooth->GetFillStyle()->SetColor(0xffffff);
	rightTooth->GetOutlineStyle()->SetColor(0x000000);
	rightTooth->GetOutlineStyle()->SetThickness(1);

	const auto leftEye = std::make_shared<CEllipse>(PointD{70, 80}, 10, 15);
	leftEye->GetFillStyle()->SetColor(0x000000);
	leftEye->GetOutlineStyle()->Disable();

	const auto rightEye = std::make_shared<CEllipse>(PointD{130, 80}, 10, 15);
	rightEye->GetFillStyle()->SetColor(0x000000);
	rightEye->GetOutlineStyle()->Disable();

	auto kurwa = std::make_shared<CShapeGroup>();
	kurwa->InsertShape(leftEar, 0);
	kurwa->InsertShape(rightEar, 1);
	kurwa->InsertShape(head, 2);
	kurwa->InsertShape(leftEye, 3);
	kurwa->InsertShape(rightEye, 4);
	kurwa->InsertShape(nose, 5);
	kurwa->InsertShape(leftTooth, 6);
	kurwa->InsertShape(rightTooth, 7);

	return kurwa;
}

std::shared_ptr<IShape> CreateCutieKitty()
{
	const auto head = std::make_shared<CEllipse>(PointD{300, 100}, 80, 70);
	head->GetFillStyle()->SetColor(0x000000);
	head->GetOutlineStyle()->Disable();

	const auto nose = std::make_shared<CTriangle>(PointD{295, 120}, PointD{300, 125}, PointD{305, 120});
	nose->GetFillStyle()->SetColor(0xfc4eb4);
	nose->GetOutlineStyle()->SetColor(0xffffff);
	nose->GetOutlineStyle()->SetThickness(1);

	const auto leftEar = std::make_shared<CTriangle>(PointD{230, 70}, PointD{250, 10}, PointD{270, 50});
	leftEar->GetFillStyle()->SetColor(0x000000);
	leftEar->GetOutlineStyle()->Disable();

	const auto rightEar = std::make_shared<CTriangle>(PointD{330, 50}, PointD{350, 10}, PointD{370, 70});
	rightEar->GetFillStyle()->SetColor(0x000000);
	rightEar->GetOutlineStyle()->Disable();

	const auto mouth = std::make_shared<CTriangle>(PointD{295, 130}, PointD{300, 135}, PointD{305, 130});
	mouth->GetFillStyle()->SetColor(0x000000);
	mouth->GetOutlineStyle()->SetColor(0xffffff);
	mouth->GetOutlineStyle()->SetThickness(2);

	const auto leftSclera = std::make_shared<CEllipse>(PointD{270, 90}, 15, 20);
	leftSclera->GetFillStyle()->SetColor(0xffffff);
	leftSclera->GetOutlineStyle()->Disable();

	const auto leftPupil = std::make_shared<CEllipse>(PointD{270, 95}, 10, 15);
	leftPupil->GetFillStyle()->SetColor(0xeb4efc);
	leftPupil->GetOutlineStyle()->Disable();

	const auto leftEye = std::make_shared<CShapeGroup>();
	leftEye->InsertShape(leftSclera, 0);
	leftEye->InsertShape(leftPupil, 1);

	const auto rightSclera = std::make_shared<CEllipse>(PointD{330, 90}, 15, 20);
	rightSclera->GetFillStyle()->SetColor(0xffffff);
	rightSclera->GetOutlineStyle()->Disable();

	const auto rightPupil = std::make_shared<CEllipse>(PointD{330, 95}, 10, 15);
	rightPupil->GetFillStyle()->SetColor(0xeb4efc);
	rightPupil->GetOutlineStyle()->Disable();

	const auto rightEye = std::make_shared<CShapeGroup>();
	rightEye->InsertShape(rightSclera, 0);
	rightEye->InsertShape(rightPupil, 1);

	auto cutieKitty = std::make_shared<CShapeGroup>();
	cutieKitty->InsertShape(leftEar, 0);
	cutieKitty->InsertShape(rightEar, 1);
	cutieKitty->InsertShape(head, 2);
	cutieKitty->InsertShape(leftEye, 3);
	cutieKitty->InsertShape(rightEye, 4);
	cutieKitty->InsertShape(nose, 5);
	cutieKitty->InsertShape(mouth, 6);

	return cutieKitty;
}

std::shared_ptr<IShape> CreateBackground()
{
	auto background = std::make_shared<CRectangle>(PointD{5, 5}, 400, 200);
	background->GetFillStyle()->SetColor(0x29d124);
	background->GetOutlineStyle()->SetColor(0x000000);
	background->GetOutlineStyle()->SetThickness(5);

	return background;
}

std::shared_ptr<ISlide> CreateSlide()
{
	auto slide = std::make_shared<CSlide>(800, 600);

	auto& shapes = slide->GetShapes();
	shapes.InsertShape(CreateBackground(), 0);
	shapes.InsertShape(CreateKurwa(), 1);
	shapes.InsertShape(CreateCutieKitty(), 2);

	return slide;
}

void DrawSlide(std::shared_ptr<ISlide> const& slide)
{
	std::ofstream output(OUTPUT_FILENAME);
	if (!output.is_open())
	{
		throw std::runtime_error("failed to create the picture");
	}

	CCanvas canvas(output, slide->GetWidth(), slide->GetHeight());

	slide->Draw(canvas);
}

int main()
{
	try
	{
		auto const slide = CreateSlide();
		DrawSlide(slide);
	}
	catch (std::exception const& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
