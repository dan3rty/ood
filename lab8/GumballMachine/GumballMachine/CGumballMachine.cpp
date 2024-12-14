#include "CGumballMachine.h"
#include "../State/HasQuarterState/CHasQuarterState.h"
#include "../State/NoQuarterState/CNoQuarterState.h"
#include "../State/SoldOutState/CSoldOutState.h"
#include "../State/SoldState/CSoldState.h"
#include <iostream>
#include <memory>
#include <sstream>

CGumballMachine::CGumballMachine(const unsigned int ballCount)
	: m_ballCount(ballCount)
{
	if (m_ballCount > 0)
	{
		CGumballMachine::SetNoQuarterState();
	}
	else
	{
		CGumballMachine::SetSoldOutState();
	}
}

void CGumballMachine::EjectQuarter() const
{
	m_currentState->EjectQuarters();
}

void CGumballMachine::InsertQuarter() const
{
	m_currentState->InsertQuarter();
}

void CGumballMachine::TurnCrank() const
{
	m_currentState->TurnCrank();
	m_currentState->Dispense();
}

void CGumballMachine::Refill(const unsigned int count) const
{
	m_currentState->Refill(count);
}

std::string CGumballMachine::ToString() const
{
	std::ostringstream ss;
	ss << "Mighty Gumball, Inc." << std::endl
	   << "C++-enabled Standing Gumball Model #2016 (with state)" << std::endl
	   << "Inventory: " << m_ballCount << " gumball" << (m_ballCount != 1 ? "s" : "") << std::endl
	   << "Quarters: " << m_quarterCount << std::endl
	   << "Machine is " << m_currentState->ToString() << std::endl;

	return ss.str();
}

void CGumballMachine::ReleaseBall()
{
	if (m_ballCount != 0)
	{
		std::cout << "A gumball comes rolling out the slot..." << std::endl;
		--m_ballCount;
	}
}

unsigned int CGumballMachine::GetBallCount() const
{
	return m_ballCount;
}

void CGumballMachine::AddBalls(const unsigned int count)
{
	m_ballCount += count;
}

void CGumballMachine::AddQuarter()
{
	++m_quarterCount;
}

void CGumballMachine::ReleaseQuarters(const unsigned int count)
{
	if (m_quarterCount != 0)
	{
		m_quarterCount -= std::min(m_quarterCount, count);
	}
}

unsigned int CGumballMachine::GetQuarterCount() const
{
	return m_quarterCount;
}

unsigned int CGumballMachine::GetMaxQuarterCount() const
{
	return MAX_QUARTER_COUNT;
}

void CGumballMachine::SetSoldOutState()
{
	m_currentState = std::make_unique<CSoldOutState>(static_cast<IGumballMachine&>(*this));
}

void CGumballMachine::SetNoQuarterState()
{
	m_currentState = std::make_unique<CNoQuarterState>(static_cast<IGumballMachine&>(*this));
}

void CGumballMachine::SetSoldState()
{
	m_currentState = std::make_unique<CSoldState>(static_cast<IGumballMachine&>(*this));
}

void CGumballMachine::SetHasQuarterState()
{
	m_currentState = std::make_unique<CHasQuarterState>(static_cast<IGumballMachine&>(*this));
}
