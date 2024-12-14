#pragma once

#include "../State/IGumballMachine.h"
#include "../State/IState.h"
#include <memory>

class CGumballMachine final : private IGumballMachine
{
public:
	explicit CGumballMachine(unsigned int ballCount);

	void EjectQuarter() const;
	void InsertQuarter() const;
	void TurnCrank() const;
	void Refill(unsigned int count) const;

	[[nodiscard]] std::string ToString() const;

private:
	static constexpr unsigned int MAX_QUARTER_COUNT = 5;

	void ReleaseBall() override;
	[[nodiscard]] unsigned int GetBallCount() const override;
	void AddBalls(unsigned int count) override;

	void AddQuarter() override;
	void ReleaseQuarters(unsigned int count) override;
	[[nodiscard]] unsigned int GetQuarterCount() const override;
	[[nodiscard]] unsigned int GetMaxQuarterCount() const override;

	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

	unsigned int m_ballCount = 0;
	unsigned int m_quarterCount = 0;
	std::unique_ptr<IState> m_currentState;
};
