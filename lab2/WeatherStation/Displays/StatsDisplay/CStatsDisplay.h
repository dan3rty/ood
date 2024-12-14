#pragma once

#include "../../WeatherData/CWeatherData.h"
#include "StatsMonitor/CStatsMonitor.h"
#include <string>

class CStatsDisplay final : public IObserver<WeatherInfo>
{
private:
    void Update(WeatherInfo const& data) override;

    static void PrintStats(std::string const& header, Stats const& stats);

    CStatsMonitor m_temperatureMonitor;
    CStatsMonitor m_humidityMonitor;
    CStatsMonitor m_pressureMonitor;
};