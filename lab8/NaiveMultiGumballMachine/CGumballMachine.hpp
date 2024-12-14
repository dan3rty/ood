#pragma once

#include <iostream>
#include <sstream>

class CGumballMachine
{
public:
	enum class State
	{
		SoldOut,
		NoQuarter,
		HasQuarter,
		Sold,
	};

	explicit CGumballMachine(const unsigned count)
		: m_ballCount(count)
		, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
	{
	}

	void InsertQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You can't insert a quarter, the machine is sold out" << std::endl;
			break;
		case State::NoQuarter:
			cout << "You inserted a quarter" << std::endl;
			m_state = State::HasQuarter;
			++m_quarterCount;
			break;
		case State::HasQuarter:
			cout << "You can't insert another quarter" << std::endl;
			break;
		case State::Sold:
			cout << "Please wait, we're already giving you a gumball" << std::endl;
			break;
		}
	}

	void EjectQuarter()
	{
		using namespace std;
		switch (m_state)
		{
		case State::HasQuarter:
			cout << "Quarters returned: " << m_quarterCount << std::endl;
			m_state = State::NoQuarter;
			m_quarterCount = 0;
			break;
		case State::NoQuarter:
			cout << "You haven't inserted a quarter" << std::endl;
			break;
		case State::Sold:
			cout << "Sorry you already turned the crank" << std::endl;
			break;
		case State::SoldOut:
			cout << "You can't eject, you haven't inserted a quarter yet" << std::endl;
			break;
		}
	}

	void TurnCrank()
	{
		using namespace std;
		switch (m_state)
		{
		case State::SoldOut:
			cout << "You turned but there's no gumballs" << std::endl;
			break;
		case State::NoQuarter:
			cout << "You turned but there's no quarter" << std::endl;
			break;
		case State::HasQuarter:
			cout << "You turned..." << std::endl;
			m_state = State::Sold;
			Dispense();
			break;
		case State::Sold:
			cout << "Turning twice doesn't get you another gumball" << std::endl;
			break;
		}
	}

	void Refill(const unsigned numBalls)
	{
		if (m_state == State::Sold)
		{
			std::cout << "Cannot refill while dispensing a gumball." << std::endl;
			return;
		}
		m_ballCount += numBalls;
		m_state = numBalls > 0 ? (m_quarterCount > 0 ? State::HasQuarter : State::NoQuarter) : State::SoldOut;
	}

	[[nodiscard]] std::string ToString() const
	{
		std::ostringstream ss;
		ss << "Mighty Gumball, Inc." << std::endl
		   << "C++-enabled Standing Gumball Model #2016 (with state)" << std::endl
		   << "Inventory: " << m_ballCount << " gumball" << (m_ballCount != 1 ? "s" : "") << std::endl
		   << "Quarters: " << m_quarterCount << std::endl
		   << "Machine is " << StateToString() << std::endl;

		return ss.str();
	}

private:
	void Dispense()
	{
		using namespace std;
		switch (m_state)
		{
		case State::Sold:
			cout << "A gumball comes rolling out the slot" << std::endl;
			--m_ballCount;
			--m_quarterCount;

			if (m_ballCount == 0)
			{
				cout << "Oops, out of gumballs" << std::endl;
				cout << "Ejecting leftover quarters: " << m_quarterCount << std::endl;
				m_quarterCount = 0;
				m_state = State::SoldOut;
				return;
			}

			if (m_quarterCount == 0)
			{
				cout << "Out of quarters" << std::endl;
				m_state = State::NoQuarter;
				return;
			}

			cout << "Still got " << m_quarterCount << " quarters" << std::endl;
			break;
		case State::NoQuarter:
			cout << "You need to pay first" << std::endl;
			break;
		case State::SoldOut:
		case State::HasQuarter:
			cout << "No gumball dispensed" << std::endl;
			break;
		}
	}

	[[nodiscard]] std::string StateToString() const
	{
		switch (m_state)
		{
		case State::SoldOut:
			return "sold out";
		case State::NoQuarter:
			return "waiting for quarter";
		case State::HasQuarter:
			return "waiting for turn of crank";
		case State::Sold:
			return "delivering a gumball";
		default:
			return "";
		}
	}

	unsigned m_ballCount = 0;
	unsigned m_quarterCount = 0;
	State m_state = State::SoldOut;
};
