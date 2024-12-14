#define CATCH_CONFIG_MAIN
#include "../WeatherData/CWeatherData.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("safe observer deletion")
{
	GIVEN("an observable")
	{
		CWeatherData observable;

		AND_GIVEN("a suicidal observer")
		{
			class CSuicidalObserver : public IObserver<WeatherInfo>
			{
			public:
				CSuicidalObserver(IObservable<WeatherInfo>& observable, std::ostream& out)
					: m_observable(observable)
					, m_out(out)
				{
				}

			private:
				void Update(WeatherInfo const& /* data */) override
				{
					m_observable.RemoveObserver(*this);
					m_out << "I was called and survived!";
				}

				IObservable<WeatherInfo>& m_observable;
				std::ostream& m_out;
			};

			std::ostringstream out;
			CSuicidalObserver observer(observable, out);
			observable.RegisterObserver(observer, 0);

			AND_GIVEN("a few dummy observers")
			{
				class CDummyObserver : public IObserver<WeatherInfo>
				{
				private:
					void Update(WeatherInfo const& /* data */) override
					{
					}
				};

				CDummyObserver dummyObserver1;
				CDummyObserver dummyObserver2;
				observable.RegisterObserver(dummyObserver1, 1);
				observable.RegisterObserver(dummyObserver2, 2);

				WHEN("notifying observers")
				{
					observable.NotifyObservers();

					THEN("it doesn't crash and produces correct output")
					{
						REQUIRE(out.str() == "I was called and survived!");
					}
				}
			}
		}
	}
}

TEST_CASE("observers with priority")
{
	GIVEN("an observable")
	{
		CWeatherData observable;

		AND_GIVEN("observers #1 and #2")
		{
			class CObserver : public IObserver<WeatherInfo>
			{
			public:
				CObserver(std::ostream& out, int number)
					: m_out(out)
					, m_number(number)
				{
				}

			private:
				void Update(WeatherInfo const& /* data */) override
				{
					m_out << "Observer #" << m_number << "\n";
				}

				std::ostream& m_out;
				int m_number;
			};

			std::ostringstream out;
			CObserver observer1(out, 1);
			CObserver observer2(out, 2);

			WHEN("adding #1 with priority 1 and #2 with priority 2 and notifying them")
			{
				observable.RegisterObserver(observer1, 1);
				observable.RegisterObserver(observer2, 2);
				observable.NotifyObservers();

				THEN("#1 gets called first, then #2")
				{
					REQUIRE(out.str() == "Observer #1\nObserver #2\n");
				}
			}

			WHEN("adding #1 with priority 5 and #2 with priority 1 and notifying them")
			{
				observable.RegisterObserver(observer1, 5);
				observable.RegisterObserver(observer2, 1);
				observable.NotifyObservers();

				THEN("#2 gets called first, then #1")
				{
					REQUIRE(out.str() == "Observer #2\nObserver #1\n");
				}
			}

			WHEN("adding both observers with the same priority (#1 first) and notifying them")
			{
				observable.RegisterObserver(observer1, 1);
				observable.RegisterObserver(observer2, 1);
				observable.NotifyObservers();

				THEN("they are called in the order of registering: #1 gets called first, then #2")
				{
					REQUIRE(out.str() == "Observer #1\nObserver #2\n");
				}
			}

			WHEN("adding both observers with the same priority (#2 first) and notifying them")
			{
				observable.RegisterObserver(observer2, 1);
				observable.RegisterObserver(observer1, 1);
				observable.NotifyObservers();

				THEN("they are called in the order of registering: #2 gets called first, then #1")
				{
					REQUIRE(out.str() == "Observer #2\nObserver #1\n");
				}
			}
		}
	}
}