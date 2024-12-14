#include "CStatsDisplay.h"
#include <iostream>

void CStatsDisplay::Update(Observable& observable, WeatherInfo const& data)
{
    auto& observableData = m_observablesData[&observable];

    observableData.temperatureMonitor.Update(data.temperature);
    observableData.humidityMonitor.Update(data.humidity);
    observableData.pressureMonitor.Update(data.pressure);

    PrintHeader(observable);
    PrintStats("Temperature", observableData.temperatureMonitor.GetStats());
    PrintStats("Humidity", observableData.humidityMonitor.GetStats());
    PrintStats("Pressure", observableData.pressureMonitor.GetStats());

    if (data.windInfo)
    {
        observableData.windSpeedMonitor.Update(data.windInfo->speed);
        observableData.windDirectionMonitor.Update(data.windInfo->direction);
        PrintStats("Wind speed", observableData.windSpeedMonitor.GetStats());
        PrintAngleStats("Wind direction", observableData.windDirectionMonitor.GetStats());
    }
}

void CStatsDisplay::SetObservableName(Observable& observable, std::string const& name)
{
    m_observablesData[&observable].name = name;
}

void CStatsDisplay::RemoveObservable(Observable& observable)
{
    m_observablesData.erase(&observable);
}

void CStatsDisplay::PrintStats(std::string const& header, Stats const& stats)
{
    std::cout << "[" << header << "]\n"
              << "Max " << stats.max << "\n"
              << "Min " << stats.min << "\n"
              << "Average " << stats.average << "\n"
              << "----------------" << std::endl;
}

void CStatsDisplay::PrintAngleStats(std::string const& header, AngleStats const& stats)
{
    std::cout << "[" << header << "]\n"
              << "Average " << stats.average << "\n"
              << "----------------" << std::endl;
}

void CStatsDisplay::PrintHeader(Observable& observable) const
{
    std::cout << "Stats from ";

    auto observableData = m_observablesData.find(&observable);
    if (observableData != m_observablesData.end())
    {
        std::cout << observableData->second.name;
    }
    else
    {
        std::cout << "unknown";
    }

    std::cout << " source\n";
}