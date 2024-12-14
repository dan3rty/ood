#pragma once

#include "../../WeatherData/CWeatherData.h"
#include "StatsMonitor/CStatsMonitor.h"
#include <map>
#include <string>

class CStatsDisplay final : public IObserver<WeatherInfo>
{
public:
    using Observable = IObservable<WeatherInfo>;

    void SetObservableName(Observable& observable, std::string const& name);
    void RemoveObservable(Observable & observable);

private:
    void Update(Observable& observable, WeatherInfo const& data) override;

    static void PrintStats(std::string const& header, Stats const& stats);
    void PrintHeader(Observable& observable) const;

    struct ObservableInfo
    {
        std::string name;

        CStatsMonitor temperatureMonitor;
        CStatsMonitor humidityMonitor;
        CStatsMonitor pressureMonitor;
    };

    std::map<Observable*, ObservableInfo> m_observablesData;
};