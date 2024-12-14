#include "CSoldState.h"
#include <iostream>

CSoldState::CSoldState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void CSoldState::InsertQuarter()
{
	std::cout << "Please wait, we're already giving you a gumball" << std::endl;
}

void CSoldState::EjectQuarters()
{
	std::cout << "Sorry you already turned the crank" << std::endl;
}

void CSoldState::TurnCrank()
{
	std::cout << "Turning twice doesn't get you another gumball" << std::endl;
}

void CSoldState::Dispense()
{
	m_gumballMachine.ReleaseBall();
	m_gumballMachine.ReleaseQuarters(1);

	if (m_gumballMachine.GetBallCount() == 0)
	{
		std::cout << "Oops, out of gumballs" << std::endl;

		if (m_gumballMachine.GetQuarterCount() > 0)
		{
			std::cout << "Ejecting leftover quarters: " << m_gumballMachine.GetQuarterCount() << std::endl;
			m_gumballMachine.ReleaseQuarters(m_gumballMachine.GetQuarterCount());
		}

		m_gumballMachine.SetSoldOutState();
		return;
	}

	if (m_gumballMachine.GetQuarterCount() == 0)
	{
		std::cout << "Out of quarters" << std::endl;
		m_gumballMachine.SetNoQuarterState();
		return;
	}

	std::cout << "Still got " << m_gumballMachine.GetQuarterCount() << " quarters" << std::endl;
	m_gumballMachine.SetHasQuarterState();
}

void CSoldState::Refill(unsigned int count)
{
	std::cout << "Can't refill while delivering a gumball" << std::endl;
}

std::string CSoldState::ToString() const
{
	return "delivering a gumball";
}
