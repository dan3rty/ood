#pragma once

#include "../../WeatherData/CWeatherData.h"
#include "StatsMonitor/CAngleStatsMonitor.h"
#include "StatsMonitor/CStatsMonitor.h"
#include <string>
#include <map>

class CStatsDisplay : public IObserver<WeatherInfo>
{
public:
    using Observable = IObservable<WeatherInfo>;

    void SetObservableName(Observable& observable, std::string const& name);
    void RemoveObservable(Observable& observable);

private:
    void Update(Observable& observable, WeatherInfo const& data) override;

    static void PrintStats(std::string const& header, Stats const& stats);
    static void PrintAngleStats(std::string const& header, AngleStats const& stats);
    void PrintHeader(Observable& observable) const;

    struct ObservableInfo
    {
        std::string name;

        CStatsMonitor temperatureMonitor;
        CStatsMonitor humidityMonitor;
        CStatsMonitor pressureMonitor;
        CStatsMonitor windSpeedMonitor;
        CAngleStatsMonitor windDirectionMonitor;
    };

    std::map<Observable*, ObservableInfo> m_observablesData;
};