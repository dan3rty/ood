#pragma once

#include "../Observer/CObservable.hpp"
#include <optional>

struct WindInfo
{
    double speed = 0;
    double direction = 0;
};

struct WeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;

    std::optional<WindInfo> windInfo;
};

template <typename Base>
class CBaseWeatherData : public Base
{
public:
    [[nodiscard]] double GetTemperature() const
    {
        return m_temperature;
    }

    [[nodiscard]] double GetHumidity() const
    {
        return m_humidity;
    }

    [[nodiscard]] double GetPressure() const
    {
        return m_pressure;
    }

    void MeasurementsChanged()
    {
        Base::NotifyObservers();
    }

    void SetMeasurements(double temperature, double humidity, double pressure)
    {
        m_temperature = temperature;
        m_humidity = humidity;
        m_pressure = pressure;

        MeasurementsChanged();
    }

protected:
    [[nodiscard]] WeatherInfo GetChangedData() const override
    {
        return {
            .temperature = GetTemperature(),
            .humidity = GetHumidity(),
            .pressure = GetPressure(),
        };
    }

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
};

using CWeatherData = CBaseWeatherData<CObservable<WeatherInfo>>;