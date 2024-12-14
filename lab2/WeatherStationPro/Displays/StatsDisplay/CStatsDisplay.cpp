#include "CStatsDisplay.h"
#include <iostream>

void CStatsDisplay::Update(WeatherInfo const& data)
{
    m_temperatureMonitor.Update(data.temperature);
    m_humidityMonitor.Update(data.humidity);
    m_pressureMonitor.Update(data.pressure);
    m_windSpeedMonitor.Update(data.windSpeed);
    m_windDirectionMonitor.Update(data.windDirection);

    PrintStats("Temperature", m_temperatureMonitor.GetStats());
    PrintStats("Humidity", m_humidityMonitor.GetStats());
    PrintStats("Pressure", m_pressureMonitor.GetStats());
    PrintStats("Wind speed", m_windSpeedMonitor.GetStats());
    PrintAngleStats("Wind direction", m_windDirectionMonitor.GetStats());
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