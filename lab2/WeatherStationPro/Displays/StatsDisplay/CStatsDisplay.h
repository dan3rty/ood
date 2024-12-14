#pragma once

#include "../../WeatherDataPro/CWeatherDataPro.h"
#include "StatsMonitor/CAngleStatsMonitor.h"
#include "StatsMonitor/CStatsMonitor.h"
#include <string>

class CStatsDisplay final : public IObserver<WeatherInfo>
{
private:
    void Update(WeatherInfo const& data) override;
    static void PrintStats(std::string const& header, Stats const& stats);
    static void PrintAngleStats(std::string const& header, AngleStats const& stats);

    CStatsMonitor m_temperatureMonitor;
    CStatsMonitor m_humidityMonitor;
    CStatsMonitor m_pressureMonitor;
    CStatsMonitor m_windSpeedMonitor;
    CAngleStatsMonitor m_windDirectionMonitor;
};