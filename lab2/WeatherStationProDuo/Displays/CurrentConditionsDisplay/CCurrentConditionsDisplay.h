#pragma once

#include "../../WeatherData/CWeatherData.h"
#include <map>
#include <string>

class CCurrentConditionsDisplay final : public IObserver<WeatherInfo>
{
public:
    using Observable = IObservable<WeatherInfo>;

    void SetObservableName(Observable& observable, std::string const& name);
    void RemoveObservable(Observable& observable);

private:
    void Update(Observable& observable, WeatherInfo const& data) override;

    void PrintHeader(Observable& observable) const;

    std::map<Observable*, std::string> m_observableNames;
};
