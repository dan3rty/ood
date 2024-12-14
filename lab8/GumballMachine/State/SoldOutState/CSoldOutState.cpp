#include "CSoldOutState.h"
#include <iostream>

CSoldOutState::CSoldOutState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void CSoldOutState::InsertQuarter()
{
	std::cout << "You can't insert a quarter, the machine is sold out" << std::endl;
}

void CSoldOutState::EjectQuarters()
{
	std::cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
}

void CSoldOutState::TurnCrank()
{
	std::cout << "You turned but there's no gumballs" << std::endl;
}

void CSoldOutState::Dispense()
{
	std::cout << "No gumball dispensed" << std::endl;
}

void CSoldOutState::Refill(const unsigned int count)
{
	std::cout << "Added " << count << " gumballs" << std::endl;
	m_gumballMachine.AddBalls(count);
	if (m_gumballMachine.GetQuarterCount() > 0)
	{
		m_gumballMachine.SetHasQuarterState();
	}
	else
	{
		m_gumballMachine.SetNoQuarterState();
	}
}

std::string CSoldOutState::ToString() const
{
	return "sold out";
}
