#include "Drawer.h"
#include "Image.h"
#include "ImageService.h"
#include <iostream>

int main()
{
	{
		Image img = ImageService::LoadImage(
			" CCCC             \n"
			"CC  CC   ##    ## \n"
			"CC      ####  ####\n"
			"CC  CC   ##    ## \n"
			" CCCC             \n");
		ImageService::Print(img, std::cout);
	}

	std::cout << std::endl;

	{
		Image img({ 30, 20 }, '.');

		Drawer::DrawLine(img, { 5, 8 }, { 15, 1 }, '#');
		Drawer::DrawLine(img, { 15, 1 }, { 25, 8 }, '#');
		Drawer::DrawLine(img, { 5, 8 }, { 25, 8 }, '#');

		Drawer::DrawLine(img, { 5, 8 }, { 5, 18 }, '#');
		Drawer::DrawLine(img, { 25, 8 }, { 25, 18 }, '#');
		Drawer::DrawLine(img, { 5, 18 }, { 25, 18 }, '#');

		Drawer::DrawCircle(img, { 15, 13 }, 3, '*');

		ImageService::Print(img, std::cout);
	}

	{
		Image img({ 30, 20 }, 0xFFFFFF);

		Drawer::DrawLine(img, { 5, 8 }, { 15, 1 }, 0xFFD700);
		Drawer::DrawLine(img, { 15, 1 }, { 25, 8 }, 0xFFD700);
		Drawer::DrawLine(img, { 5, 8 }, { 25, 8 }, 0xFFD700);

		Drawer::DrawLine(img, { 5, 8 }, { 5, 18 }, 0x8B4513);
		Drawer::DrawLine(img, { 25, 8 }, { 25, 18 }, 0x8B4513);
		Drawer::DrawLine(img, { 5, 18 }, { 25, 18 }, 0x8B4513);

		// уголок говнище с радиусом 4
		Drawer::FillCircle(img, { 15, 13 }, 4, 0xADD8E6);
		Drawer::DrawCircle(img, { 15, 13 }, 4, 0x0000FF);

		ImageService::SaveImageToPPM(img, "house.ppm");
	}

	return EXIT_SUCCESS;
}
