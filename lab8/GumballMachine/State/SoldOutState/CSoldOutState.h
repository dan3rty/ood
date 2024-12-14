#pragma once

#include "../IGumballMachine.h"
#include "../IState.h"

class CSoldOutState final : public IState
{
public:
	explicit CSoldOutState(IGumballMachine& gumballMachine);

	void InsertQuarter() override;
	void EjectQuarters() override;
	void TurnCrank() override;
	void Dispense() override;
	void Refill(unsigned int count) override;

	[[nodiscard]] std::string ToString() const override;

private:
	IGumballMachine& m_gumballMachine;
};
