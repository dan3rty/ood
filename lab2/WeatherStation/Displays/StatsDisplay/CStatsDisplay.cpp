#include "CStatsDisplay.h"
#include <iostream>

void CStatsDisplay::Update(WeatherInfo const& data)
{
    m_temperatureMonitor.Update(data.temperature);
    m_humidityMonitor.Update(data.humidity);
    m_pressureMonitor.Update(data.pressure);

    PrintStats("Temperature", m_temperatureMonitor.GetStats());
    PrintStats("Humidity", m_humidityMonitor.GetStats());
    PrintStats("Pressure", m_pressureMonitor.GetStats());
}

void CStatsDisplay::PrintStats(std::string const& header, Stats const& stats)
{
    std::cout << "[" << header << "]\n"
              << "Max " << stats.max << "\n"
              << "Min " << stats.min << "\n"
              << "Average " << stats.average << "\n"
              << "----------------" << std::endl;
}