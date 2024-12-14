#include "Menu/CMenu.h"

int main()
{
	CGumballMachine gumballMachine(5);
	CMenu menu(std::cin, std::cout, gumballMachine);
	menu.Start();

	return EXIT_SUCCESS;
}
