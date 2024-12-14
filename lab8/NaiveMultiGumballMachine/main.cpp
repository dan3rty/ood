#include "CGumballMachine.hpp"

int main()
{
	CGumballMachine machine(5);

	std::cout << machine.ToString() << std::endl;

	machine.InsertQuarter();
	machine.TurnCrank();

	std::cout << machine.ToString() << std::endl;

	machine.InsertQuarter();
	machine.EjectQuarter();
	machine.TurnCrank();

	std::cout << machine.ToString() << std::endl;

	machine.InsertQuarter();
	machine.TurnCrank();
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.EjectQuarter();

	std::cout << machine.ToString() << std::endl;

	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.InsertQuarter();
	machine.TurnCrank();
	machine.InsertQuarter();
	machine.TurnCrank();

	std::cout << machine.ToString() << std::endl;

	return EXIT_SUCCESS;
}
