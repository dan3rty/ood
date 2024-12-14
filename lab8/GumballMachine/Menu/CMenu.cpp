#include "CMenu.h"
#include <sstream>

CMenu::CMenu(std::istream& input, std::ostream& output, CGumballMachine& gumballMachine)
	: m_input(input)
	, m_output(output)
	, m_gumballMachine(gumballMachine)
{
}

void CMenu::Start()
{
	std::string command;

	while (m_running && (m_output << "> ") && std::getline(m_input, command))
	{
		std::istringstream args(command);
		std::string commandName;

		args >> commandName;

		try
		{
			auto const handler = GetCommandHandler(commandName);
			handler(args);
		}
		catch (std::exception const& e)
		{
			m_output << "Error: " << e.what() << std::endl;
		}
	}

	m_output << "Bye" << std::endl;
}
CMenu::CommandHandler CMenu::GetCommandHandler(std::string const& commandName)
{
	if (commandName == "InsertQuarter")
	{
		return [this](std::istream& /* input */) {
			InsertQuarter();
		};
	}
	if (commandName == "EjectQuarter")
	{
		return [this](std::istream& /* input */) {
			EjectQuarter();
		};
	}
	if (commandName == "TurnCrank")
	{
		return [this](std::istream& /* input */) {
			TurnCrank();
		};
	}
	if (commandName == "Refill")
	{
		return [this](std::istream& input) {
			Refill(input);
		};
	}
	if (commandName == "Status")
	{
		return [this](std::istream& /* input */) {
			Status();
		};
	}
	if (commandName == "Help")
	{
		return [this](std::istream& /* input */) {
			Help();
		};
	}
	if (commandName == "Exit")
	{
		return [this](std::istream& /* input */) {
			Exit();
		};
	}

	throw std::runtime_error("unknown command: " + commandName);
}

void CMenu::InsertQuarter() const
{
	m_gumballMachine.InsertQuarter();
}

void CMenu::EjectQuarter() const
{
	m_gumballMachine.EjectQuarter();
}

void CMenu::TurnCrank() const
{
	m_gumballMachine.TurnCrank();
}

void CMenu::Refill(std::istream& args) const
{
	unsigned int count;
	if (!(args >> count))
	{
		throw std::invalid_argument("invalid ball count");
	}

	m_gumballMachine.Refill(count);
}

void CMenu::Status() const
{
	m_output << m_gumballMachine.ToString() << std::endl;
}

void CMenu::Exit()
{
	m_running = false;
}

void CMenu::Help() const
{
	m_output << "Available commands:" << std::endl
			 << "InsertQuarter" << std::endl
			 << "EjectQuarter" << std::endl
			 << "TurnCrank" << std::endl
			 << "Refill <count_balls>" << std::endl
			 << "Status" << std::endl
			 << "Exit"
			 << std::endl;
}