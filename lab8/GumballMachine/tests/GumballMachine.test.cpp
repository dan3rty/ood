#define CATCH_CONFIG_MAIN
#include "../GumballMachine/CGumballMachine.h"
#include "../State/HasQuarterState/CHasQuarterState.h"
#include "../State/NoQuarterState/CNoQuarterState.h"
#include "../State/SoldOutState/CSoldOutState.h"
#include "../State/SoldState/CSoldState.h"
#include "catch.hpp"
#include "fakeit.hpp"

std::string BuildMachineStr(const unsigned int expectedBallCount, const unsigned int expectedQuarterCount, std::string const& expectedState)
{
	std::ostringstream ss;
	ss << "Mighty Gumball, Inc." << std::endl
	   << "C++-enabled Standing Gumball Model #2016 (with state)" << std::endl
	   << "Inventory: " << expectedBallCount << " gumball" << (expectedBallCount != 1 ? "s" : "") << std::endl
	   << "Quarters: " << expectedQuarterCount << std::endl
	   << "Machine is " << expectedState << std::endl;

	return ss.str();
}

TEST_CASE("gumball machine")
{
	GIVEN("a machine with 2 balls")
	{
		CGumballMachine machine(2);

		WHEN("it is just created")
		{
			THEN("it contains 2 balls and is in the no quarter state")
			{
				auto const str = machine.ToString();
				REQUIRE(str == BuildMachineStr(2, 0, "waiting for quarter"));
			}
		}

		WHEN("trying to turn the crank")
		{
			machine.TurnCrank();

			THEN("nothing changes")
			{
				auto const str = machine.ToString();
				REQUIRE(str == BuildMachineStr(2, 0, "waiting for quarter"));
			}
		}

		WHEN("trying to return the quarter")
		{
			machine.EjectQuarter();

			THEN("nothing changes")
			{
				auto const str = machine.ToString();
				REQUIRE(str == BuildMachineStr(2, 0, "waiting for quarter"));
			}
		}

		WHEN("refilling with 3 balls")
		{
			machine.Refill(3);

			THEN("balls are added and state is the same")
			{
				auto const str = machine.ToString();
				REQUIRE(str == BuildMachineStr(5, 0, "waiting for quarter"));
			}
		}

		WHEN("inserting a quarter")
		{
			machine.InsertQuarter();

			THEN("machine is waiting for the crank")
			{
				auto const str = machine.ToString();
				REQUIRE(str == BuildMachineStr(2, 1, "waiting for turn of crank"));
			}

			AND_WHEN("inserting another quarter")
			{
				machine.InsertQuarter();

				THEN("machine is still waiting for the crank")
				{
					auto const str = machine.ToString();
					REQUIRE(str == BuildMachineStr(2, 2, "waiting for turn of crank"));
				}
			}

			AND_WHEN("returning the quarter")
			{
				machine.EjectQuarter();

				THEN("machine is waiting for quarter")
				{
					auto const str = machine.ToString();
					REQUIRE(str == BuildMachineStr(2, 0, "waiting for quarter"));
				}
			}

			WHEN("refilling with 3 balls")
			{
				machine.Refill(3);

				THEN("balls are added and state is the same")
				{
					auto const str = machine.ToString();
					REQUIRE(str == BuildMachineStr(5, 1, "waiting for turn of crank"));
				}
			}

			AND_WHEN("turning the crank")
			{
				machine.TurnCrank();

				THEN("a gumball is dispensed and the machine is waiting for quarter")
				{
					auto const str = machine.ToString();
					REQUIRE(str == BuildMachineStr(1, 0, "waiting for quarter"));
				}

				AND_WHEN("turning the crank again")
				{
					machine.TurnCrank();

					THEN("nothing changes")
					{
						auto const str = machine.ToString();
						REQUIRE(str == BuildMachineStr(1, 0, "waiting for quarter"));
					}
				}
			}
		}
	}

	GIVEN("a machine with 0 balls")
	{
		CGumballMachine machine(0);

		WHEN("it is just created")
		{
			THEN("it contains zero balls and is in the sold out state")
			{
				auto const str = machine.ToString();
				REQUIRE(str == BuildMachineStr(0, 0, "sold out"));
			}
		}

		WHEN("refilling with 3 balls")
		{
			machine.Refill(3);

			THEN("balls are added and the machine is no longer sold out")
			{
				auto const str = machine.ToString();
				REQUIRE(str == BuildMachineStr(3, 0, "waiting for quarter"));
			}
		}

		WHEN("inserting a quarter")
		{
			machine.InsertQuarter();

			THEN("the machine is still sold out")
			{
				auto const str = machine.ToString();
				REQUIRE(str == BuildMachineStr(0, 0, "sold out"));
			}

			AND_WHEN("turning the crank")
			{
				machine.TurnCrank();

				THEN("no balls are dispensed and the machine is still sold out")
				{
					auto const str = machine.ToString();
					REQUIRE(str == BuildMachineStr(0, 0, "sold out"));
				}
			}
		}
	}
}

TEST_CASE("states")
{
	fakeit::Mock<IGumballMachine> machineMock;

	fakeit::Fake(Method(machineMock, ReleaseBall));
	fakeit::Fake(Method(machineMock, AddBalls));

	fakeit::Fake(Method(machineMock, AddQuarter));
	fakeit::Fake(Method(machineMock, ReleaseQuarters));
	fakeit::When(Method(machineMock, GetMaxQuarterCount)).AlwaysReturn(2);

	fakeit::Fake(Method(machineMock, SetSoldOutState));
	fakeit::Fake(Method(machineMock, SetNoQuarterState));
	fakeit::Fake(Method(machineMock, SetSoldState));
	fakeit::Fake(Method(machineMock, SetHasQuarterState));

	auto& machine = machineMock.get();

	GIVEN("a sold out state")
	{
		CSoldOutState state(machine);

		WHEN("inserting a quarter")
		{
			state.InsertQuarter();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("ejecting a quarter")
		{
			state.EjectQuarters();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("turning the crank")
		{
			state.TurnCrank();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("dispensing")
		{
			state.Dispense();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("refilling with 3 balls while having 0 quarters")
		{
			fakeit::When(Method(machineMock, GetQuarterCount)).Return(0);
			state.Refill(3);

			THEN("3 balls are added and no quarter state is set")
			{
				fakeit::Verify(Method(machineMock, AddBalls).Using(3)).Once();
				fakeit::Verify(Method(machineMock, SetNoQuarterState)).Once();
			}
		}
	}

	GIVEN("no quarter state")
	{
		fakeit::When(Method(machineMock, GetQuarterCount)).AlwaysReturn(0);
		CNoQuarterState state(machine);

		WHEN("inserting a quarter")
		{
			state.InsertQuarter();

			THEN("has quarter state is set")
			{
				fakeit::Verify(Method(machineMock, SetHasQuarterState)).Once();
			}
		}

		WHEN("ejecting a quarter")
		{
			state.EjectQuarters();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("turning the crank")
		{
			state.TurnCrank();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("dispensing")
		{
			state.Dispense();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("refilling with 3 balls")
		{
			state.Refill(3);

			THEN("3 balls are added")
			{
				fakeit::Verify(Method(machineMock, AddBalls).Using(3)).Once();
			}
		}
	}

	GIVEN("has quarter state")
	{
		fakeit::When(Method(machineMock, GetQuarterCount)).AlwaysReturn(1);
		CHasQuarterState state(machine);

		WHEN("inserting a quarter")
		{
			state.InsertQuarter();

			THEN("another quarter is added")
			{
				fakeit::Verify(Method(machineMock, AddQuarter));
			}
		}

		WHEN("ejecting a quarter")
		{
			state.EjectQuarters();

			THEN("no quarter state is set")
			{
				fakeit::Verify(Method(machineMock, SetNoQuarterState)).Once();
			}
		}

		WHEN("turning the crank")
		{
			state.TurnCrank();

			THEN("sold state is set")
			{
				fakeit::Verify(Method(machineMock, SetSoldState)).Once();
			}
		}

		WHEN("dispensing")
		{
			state.Dispense();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("refilling with 3 balls")
		{
			state.Refill(3);

			THEN("3 balls are added")
			{
				fakeit::Verify(Method(machineMock, AddBalls).Using(3)).Once();
			}
		}
	}

	GIVEN("sold state")
	{
		CSoldState state(machine);

		WHEN("inserting a quarter")
		{
			state.InsertQuarter();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("ejecting a quarter")
		{
			state.EjectQuarters();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("turning the crank")
		{
			state.TurnCrank();

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}

		WHEN("dispensing with filled machine")
		{
			fakeit::When(Method(machineMock, GetBallCount)).Return(5);
			fakeit::When(Method(machineMock, GetQuarterCount)).AlwaysReturn(0);
			state.Dispense();

			THEN("no quarter state is set")
			{
				fakeit::Verify(Method(machineMock, SetNoQuarterState));
			}
		}

		WHEN("dispensing with empty machine")
		{
			fakeit::When(Method(machineMock, GetBallCount)).Return(0);
			fakeit::When(Method(machineMock, GetQuarterCount)).AlwaysReturn(0);
			state.Dispense();

			THEN("sold out state is set")
			{
				fakeit::Verify(Method(machineMock, SetSoldOutState));
			}
		}

		WHEN("refilling with 3 balls")
		{
			state.Refill(3);

			THEN("nothing happens")
			{
				fakeit::VerifyNoOtherInvocations(machineMock);
			}
		}
	}
}

TEST_CASE("several quarters")
{
	fakeit::Mock<IGumballMachine> machineMock;

	fakeit::Fake(Method(machineMock, ReleaseBall));

	fakeit::When(Method(machineMock, GetMaxQuarterCount)).AlwaysReturn(2);

	fakeit::Fake(Method(machineMock, SetSoldOutState));
	fakeit::Fake(Method(machineMock, SetNoQuarterState));
	fakeit::Fake(Method(machineMock, SetSoldState));
	fakeit::Fake(Method(machineMock, SetHasQuarterState));

	auto& machine = machineMock.get();

	GIVEN("has quarter state with 1 quarter and 3 gumballs")
	{
		unsigned int quarters = 1;
		fakeit::When(Method(machineMock, AddQuarter)).AlwaysDo([&quarters]() {
			++quarters;
		});
		fakeit::When(Method(machineMock, ReleaseQuarters)).AlwaysDo([&quarters](unsigned int count) {
			quarters -= std::min(quarters, count);
		});
		fakeit::When(Method(machineMock, GetQuarterCount)).AlwaysDo([&quarters]() {
			return quarters;
		});
		fakeit::When(Method(machineMock, GetBallCount)).AlwaysReturn(3);

		CHasQuarterState state(machine);

		WHEN("turning the crank")
		{
			state.TurnCrank();

			THEN("sold state is set")
			{
				fakeit::Verify(Method(machineMock, SetSoldState)).Once();
			}
		}

		WHEN("inserting a quarter")
		{
			state.InsertQuarter();

			THEN("1 quarter is added")
			{
				REQUIRE(quarters == 2);
			}

			AND_WHEN("trying to insert another quarter")
			{
				state.InsertQuarter();

				THEN("no quarters are added")
				{
					REQUIRE(quarters == 2);
				}
			}

			AND_WHEN("ejecting quarters")
			{
				state.EjectQuarters();

				THEN("all quarters are ejected")
				{
					REQUIRE(quarters == 0);
				}
			}

			AND_WHEN("turning the crank")
			{
				state.TurnCrank();

				THEN("sold state is set")
				{
					fakeit::Verify(Method(machineMock, SetSoldState)).Once();
				}
			}
		}
	}

	GIVEN("sold state with 2 quarters and 3 gumballs")
	{
		unsigned int quarters = 2;
		fakeit::When(Method(machineMock, ReleaseQuarters)).AlwaysDo([&quarters](unsigned int count) {
			quarters -= std::min(quarters, count);
		});
		fakeit::When(Method(machineMock, GetQuarterCount)).AlwaysDo([&quarters]() {
			return quarters;
		});
		fakeit::When(Method(machineMock, GetBallCount)).AlwaysReturn(3);

		CSoldState state(machine);

		WHEN("dispensing")
		{
			state.Dispense();

			THEN("1 quarter is released")
			{
				REQUIRE(quarters == 1);
			}

			THEN("has quarter state is set")
			{
				fakeit::Verify(Method(machineMock, SetHasQuarterState)).Once();
			}
		}
	}

	GIVEN("sold state with 1 quarter and 3 gumballs")
	{
		unsigned int quarters = 1;
		fakeit::When(Method(machineMock, ReleaseQuarters)).AlwaysDo([&quarters](unsigned int count) {
			quarters -= std::min(quarters, count);
		});
		fakeit::When(Method(machineMock, GetQuarterCount)).AlwaysDo([&quarters]() {
			return quarters;
		});
		fakeit::When(Method(machineMock, GetBallCount)).AlwaysReturn(3);

		CSoldState state(machine);

		WHEN("dispensing")
		{
			state.Dispense();

			THEN("1 quarter is released")
			{
				REQUIRE(quarters == 0);
			}

			THEN("no quarter state is set")
			{
				fakeit::Verify(Method(machineMock, SetNoQuarterState)).Once();
			}
		}
	}

	GIVEN("sold state with 3 quarters and no gumballs")
	{
		unsigned int quarters = 3;
		fakeit::When(Method(machineMock, ReleaseQuarters)).AlwaysDo([&quarters](unsigned int count) {
			quarters -= std::min(quarters, count);
		});
		fakeit::When(Method(machineMock, GetQuarterCount)).AlwaysDo([&quarters]() {
			return quarters;
		});
		fakeit::When(Method(machineMock, GetBallCount)).AlwaysReturn(0);

		CSoldState state(machine);

		WHEN("dispensing")
		{
			state.Dispense();

			THEN("all quarters are released with 2 being returned")
			{
				REQUIRE(quarters == 0);
			}

			THEN("sold out state is set")
			{
				fakeit::Verify(Method(machineMock, SetSoldOutState)).Once();
			}
		}
	}
}
