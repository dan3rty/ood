#include "CNoQuarterState.h"
#include <iostream>

CNoQuarterState::CNoQuarterState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void CNoQuarterState::InsertQuarter()
{
	std::cout << "You inserted a quarter" << std::endl;
	m_gumballMachine.AddQuarter();
	m_gumballMachine.SetHasQuarterState();
}

void CNoQuarterState::EjectQuarters()
{
	std::cout << "You haven't inserted a quarter" << std::endl;
}

void CNoQuarterState::TurnCrank()
{
	std::cout << "You turned but there's no quarter" << std::endl;
}

void CNoQuarterState::Dispense()
{
	std::cout << "You need to pay first" << std::endl;
}

void CNoQuarterState::Refill(const unsigned int count)
{
	std::cout << "Added " << count << " gumballs" << std::endl;
	m_gumballMachine.AddBalls(count);
}

std::string CNoQuarterState::ToString() const
{
	return "waiting for quarter";
}
