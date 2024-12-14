#pragma once

#include <string>

class IState
{
public:
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarters() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual void Refill(unsigned int count) = 0;

	[[nodiscard]] virtual std::string ToString() const = 0;

	virtual ~IState() = default;
};
