#define CATCH_CONFIG_MAIN
#include "../WeatherData/CWeatherData.h"
#include "catch.hpp"
#include <sstream>

TEST_CASE("several observables in the same observers")
{
	GIVEN("a few observables")
	{
		CWeatherData observable1;
		CWeatherData observable2;

		AND_GIVEN("an observer")
		{
			class CDummyObserver : public IObserver<WeatherInfo>
			{
			public:
				explicit CDummyObserver(std::ostream& out)
					: m_out(out)
				{
				}

				void SetObservableName(IObservable<WeatherInfo>& observable, std::string const& name)
				{
					m_observableNames[&observable] = name;
				}

				void RemoveObservable(IObservable<WeatherInfo>& observable)
				{
					m_observableNames.erase(&observable);
				}

			private:
				void Update(IObservable<WeatherInfo>& observable, WeatherInfo const& data) override
				{
					auto name = m_observableNames.find(&observable);
					if (name != m_observableNames.end())
					{
						m_out << name->second;
					}
					else
					{
						m_out << "unknown";
					}

					m_out << '\n';
				}

				std::map<IObservable<WeatherInfo>*, std::string> m_observableNames;
				std::ostream& m_out;
			};

			std::ostringstream out;
			CDummyObserver observer(out);

			observable1.RegisterObserver(observer);
			observable2.RegisterObserver(observer);

			WHEN("notifying from both observables")
			{
				observable1.NotifyObservers();
				observable2.NotifyObservers();

				THEN("both of them are unknown")
				{
					REQUIRE(out.str() == "unknown\nunknown\n");
				}
			}

			WHEN("settings names for observables")
			{
				observer.SetObservableName(observable1, "1");
				observer.SetObservableName(observable2, "2");

				AND_WHEN("notifying from both observables")
				{
					observable1.NotifyObservers();
					observable2.NotifyObservers();

					THEN("they have different names")
					{
						REQUIRE(out.str() == "1\n2\n");
					}
				}

				AND_WHEN("removing info about first observable")
				{
					observer.RemoveObservable(observable1);

					AND_WHEN("notifying from both observables")
					{
						observable1.NotifyObservers();
						observable2.NotifyObservers();

						THEN("first one is unknown")
						{
							REQUIRE(out.str() == "unknown\n2\n");
						}
					}
				}
			}
		}
	}
}