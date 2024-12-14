#include "CHasQuarterState.h"
#include <iostream>

CHasQuarterState::CHasQuarterState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void CHasQuarterState::InsertQuarter()
{
	if (m_gumballMachine.GetQuarterCount() == m_gumballMachine.GetMaxQuarterCount())
	{
		std::cout << "You can't insert another quarter" << std::endl;
		return;
	}

	std::cout << "You inserted a quarter" << std::endl;
	m_gumballMachine.AddQuarter();
}

void CHasQuarterState::EjectQuarters()
{
	std::cout << "Quarter returned" << std::endl;
	m_gumballMachine.ReleaseQuarters(m_gumballMachine.GetQuarterCount());
	m_gumballMachine.SetNoQuarterState();
}

void CHasQuarterState::TurnCrank()
{
	std::cout << "You turned..." << std::endl;
	m_gumballMachine.SetSoldState();
}

void CHasQuarterState::Dispense()
{
	std::cout << "No gumball dispensed" << std::endl;
}

void CHasQuarterState::Refill(const unsigned int count)
{
	std::cout << "Added " << count << " gumballs. "
			  << "There are still " << m_gumballMachine.GetQuarterCount() << " quarters left" << std::endl;
	m_gumballMachine.AddBalls(count);
}

std::string CHasQuarterState::ToString() const
{
	return "waiting for turn of crank";
}
