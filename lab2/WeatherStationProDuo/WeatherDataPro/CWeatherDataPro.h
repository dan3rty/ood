#pragma once

#include "../Observer/CObservable.hpp"
#include "../WeatherData/CWeatherData.h"
// должно быть 2 обсерверебла (2 разные даты)
class CWeatherDataPro final : public CBaseWeatherData<CObservable<WeatherInfo>>
{
public:
    [[nodiscard]] double GetWindSpeed() const;
    [[nodiscard]] double GetWindDirection() const;

    void SetMeasurements(double temperature, double humidity, double pressure, double windSpeed, double windDirection);

protected:
    [[nodiscard]] WeatherInfo GetChangedData() const override;

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;

    double m_windSpeed = 0;
    double m_windDirection = 0;
};