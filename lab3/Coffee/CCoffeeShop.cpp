#include "CCoffeeShop.h"
#include "Beverages/Cappuccino/CCappuccino.h"
#include "Beverages/Latte/CLatte.h"
#include "Beverages/Milkshake/CMilkshake.h"
#include "Beverages/Tea/CTea.h"
#include "Condiments/ChocolateCrumbs/CChocolateCrumbs.h"
#include "Condiments/ChocolateSlices/CChocolateSlices.h"
#include "Condiments/Cinnamon/CCinnamon.h"
#include "Condiments/CoconutFlakes/CCoconutFlakes.h"
#include "Condiments/Cream/CCream.h"
#include "Condiments/IceCubes/CIceCubes.h"
#include "Condiments/Lemon/CLemon.h"
#include "Condiments/Liqueur/CLiqueur.h"
#include "Condiments/Syrup/CSyrup.h"
#include <iostream>

void CCoffeeShop::Start()
{
	std::cout << "Welcome to the coffee shop! What would you like?\n";

	if (!SelectBeverage())
	{
		std::cout << "Sorry, we don't serve this here\n";
		return;
	}

	std::cout << "Your drink is coming right up.\n"
				 "We have a wide variety of different condiments, feel free to pick anything you like\n";
	for (;;)
	{
		bool result;
		try
		{
			result = SelectCondiment();
		}
		catch (std::exception&)
		{
			std::cout << "I didn't quite get that..\n";
			return;
		}

		if (result)
		{
			std::cout << "And.. done! Anything else?\n";
		}
		else
		{
			break;
		}
	}

	std::cout << "I guess that's all for now. Here's your beverage, enjoy!\n"
			  << m_beverage->GetDescription() << ", cost: " << m_beverage->GetCost() << " RUB\n"
			  << "Visit us again!" << std::endl;
}

bool CCoffeeShop::SelectBeverage()
{
	int userChoice;

	std::cout << "1 - Cappuccino\n2 - Latte\n3 - Milkshake\n4 - Tea\n> ";
	std::cin >> userChoice;

	switch (userChoice)
	{
	case 1:
		return SelectCappuccino();
	case 2:
		return SelectLatte();
	case 3:
		return SelectMilkshake();
	case 4:
		return SelectTea();
	default:
		return false;
	}
}

bool CCoffeeShop::SelectCappuccino()
{
	int userChoice;

	std::cout << "1 - Standard, 2 - Double\n> ";
	std::cin >> userChoice;

	switch (userChoice)
	{
	case 1:
		m_beverage = std::make_unique<CCappuccino>(CoffeePortion::Standard);
		return true;
	case 2:
		m_beverage = std::make_unique<CCappuccino>(CoffeePortion::Double);
		return true;
	default:
		return false;
	}
}

bool CCoffeeShop::SelectLatte()
{
	int userChoice;

	std::cout << "1 - Standard, 2 - Double\n> ";
	std::cin >> userChoice;

	switch (userChoice)
	{
	case 1:
		m_beverage = std::make_unique<CLatte>(CoffeePortion::Standard);
		return true;
	case 2:
		m_beverage = std::make_unique<CLatte>(CoffeePortion::Double);
		return true;
	default:
		return false;
	}
}

bool CCoffeeShop::SelectMilkshake()
{
	int userChoice;

	std::cout << "1 - Small, 2 - Standard, 3 - Grand\n> ";
	std::cin >> userChoice;

	switch (userChoice)
	{
	case 1:
		m_beverage = std::make_unique<CMilkshake>(MilkshakePortion::Small);
		return true;
	case 2:
		m_beverage = std::make_unique<CMilkshake>(MilkshakePortion::Standard);
		return true;
	case 3:
		m_beverage = std::make_unique<CMilkshake>(MilkshakePortion::Grand);
		return true;
	default:
		return false;
	}
}

bool CCoffeeShop::SelectTea()
{
	int userChoice;

	std::cout << "1 - Black, 2 - Green, 3 - Oolong, 4 - Karkade\n> ";
	std::cin >> userChoice;

	switch (userChoice)
	{
	case 1:
		m_beverage = std::make_unique<CTea>(TeaType::Black);
		return true;
	case 2:
		m_beverage = std::make_unique<CTea>(TeaType::Green);
		return true;
	case 3:
		m_beverage = std::make_unique<CTea>(TeaType::Oolong);
		return true;
	case 4:
		m_beverage = std::make_unique<CTea>(TeaType::Karkade);
		return true;
	default:
		return false;
	}
}

bool CCoffeeShop::SelectCondiment()
{
	int userChoice;

	std::cout << "1 - Chocolate crumbs\n2 - Chocolate slices\n3 - Cinnamon\n"
				 "4 - Coconut flakes\n5 - Cream\n6 - Ice cubes\n"
				 "7 - Lemon\n8 - Liqueur\n9 - Syrup\n10 - That's all\n> ";
	std::cin >> userChoice;

	switch (userChoice)
	{
	case 1:
		return AddChocolateCrumbs();
	case 2:
		return AddChocolateSlices();
	case 3:
		m_beverage = std::move(m_beverage) << MakeCondiment<CCinnamon>();
		return true;
	case 4:
		return AddCoconutFlakes();
	case 5:
		m_beverage = std::move(m_beverage) << MakeCondiment<CCream>();
		return true;
	case 6:
		return AddIceCubes();
	case 7:
		return AddLemon();
	case 8:
		return AddLiqueur();
	case 9:
		return AddSyrup();
	default:
		return false;
	}
}

bool CCoffeeShop::AddChocolateCrumbs()
{
	unsigned mass;

	std::cout << "How many grams?\n> ";
	std::cin >> mass;

	if (std::cin.bad())
	{
		return false;
	}

	m_beverage = std::move(m_beverage) << MakeCondiment<CChocolateCrumbs>(mass);
	return true;
}

bool CCoffeeShop::AddChocolateSlices()
{
	unsigned quantity;

	std::cout << "How many slices?\n> ";
	std::cin >> quantity;

	if (std::cin.bad())
	{
		return false;
	}

	m_beverage = std::move(m_beverage) << MakeCondiment<CChocolateSlices>(quantity);
	return true;
}

bool CCoffeeShop::AddCoconutFlakes()
{
	unsigned mass;

	std::cout << "How many grams?\n> ";
	std::cin >> mass;

	if (std::cin.bad())
	{
		return false;
	}

	m_beverage = std::move(m_beverage) << MakeCondiment<CCoconutFlakes>(mass);
	return true;
}

bool CCoffeeShop::AddIceCubes()
{
	int typeChoice;
	unsigned quantity;
	IceCubeType type;

	std::cout << "1 - Dry, 2 - Water\n> ";
	std::cin >> typeChoice;
	switch (typeChoice)
	{
	case 1:
		type = IceCubeType::Dry;
		break;
	case 2:
		type = IceCubeType::Water;
		break;
	default:
		return false;
	}

	std::cout << "How many cubes?\n> ";
	std::cin >> quantity;

	if (std::cin.bad())
	{
		return false;
	}

	m_beverage = std::move(m_beverage) << MakeCondiment<CIceCubes>(quantity, type);
	return true;
}

bool CCoffeeShop::AddLemon()
{
	unsigned quantity;

	std::cout << "How many slices?\n> ";
	std::cin >> quantity;

	if (std::cin.bad())
	{
		return false;
	}

	m_beverage = std::move(m_beverage) << MakeCondiment<CLemon>(quantity);
	return true;
}

bool CCoffeeShop::AddLiqueur()
{
	int typeChoice;
	LiqueurType type;

	std::cout << "1 - Nut, 2 - Chocolate\n> ";
	std::cin >> typeChoice;
	switch (typeChoice)
	{
	case 1:
		type = LiqueurType::Nut;
		break;
	case 2:
		type = LiqueurType::Chocolate;
		break;
	default:
		return false;
	}

	if (std::cin.bad())
	{
		return false;
	}

	m_beverage = std::move(m_beverage) << MakeCondiment<CLiqueur>(type);
	return true;
}

bool CCoffeeShop::AddSyrup()
{
	int typeChoice;
	SyrupType type;

	std::cout << "1 - Chocolate, 2 - Maple\n> ";
	std::cin >> typeChoice;
	switch (typeChoice)
	{
	case 1:
		type = SyrupType::Chocolate;
		break;
	case 2:
		type = SyrupType::Maple;
		break;
	default:
		return false;
	}

	if (std::cin.bad())
	{
		return false;
	}

	m_beverage = std::move(m_beverage) << MakeCondiment<CSyrup>(type);
	return true;
}