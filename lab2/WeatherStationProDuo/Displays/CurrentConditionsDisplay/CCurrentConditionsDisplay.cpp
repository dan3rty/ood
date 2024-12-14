#include "CCurrentConditionsDisplay.h"
#include <iostream>

void CCurrentConditionsDisplay::Update(Observable& observable, WeatherInfo const& data)
{
    PrintHeader(observable);

    std::cout << "Current Temp " << data.temperature << "\n"
              << "Current Hum " << data.humidity << "\n"
              << "Current Pressure " << data.pressure << "\n";

    if (data.windInfo)
    {
        std::cout << "Current Wind speed " << data.windInfo->speed << "\n"
                  << "Current Wind direction " << data.windInfo->direction << " degrees\n";
    }

    std::cout << "----------------" << std::endl;
}

void CCurrentConditionsDisplay::SetObservableName(Observable& observable, std::string const& name)
{
    m_observableNames[&observable] = name;
}

void CCurrentConditionsDisplay::RemoveObservable(Observable& observable)
{
    m_observableNames.erase(&observable);
}

void CCurrentConditionsDisplay::PrintHeader(Observable& observable) const
{
    std::cout << "Conditions from ";

    auto name = m_observableNames.find(&observable);
    if (name != m_observableNames.end())
    {
        std::cout << name->second;
    }
    else
    {
        std::cout << "unknown";
    }

    std::cout << " source\n";
}