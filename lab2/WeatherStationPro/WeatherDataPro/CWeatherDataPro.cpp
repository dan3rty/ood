#include "CWeatherDataPro.h"

double CWeatherDataPro::GetTemperature() const
{
    return m_temperature;
}

double CWeatherDataPro::GetHumidity() const
{
    return m_humidity;
}

double CWeatherDataPro::GetPressure() const
{
    return m_pressure;
}

double CWeatherDataPro::GetWindSpeed() const
{
    return m_windSpeed;
}

double CWeatherDataPro::GetWindDirection() const
{
    return m_windDirection;
}

void CWeatherDataPro::MeasurementsChanged()
{
    NotifyObservers();
}

void CWeatherDataPro::SetMeasurements(double temperature, double humidity, double pressure, double windSpeed, double windDirection)
{
    m_temperature = temperature;
    m_humidity = humidity;
    m_pressure = pressure;
    m_windSpeed = windSpeed;
    m_windDirection = windDirection;

    MeasurementsChanged();
}

WeatherInfo CWeatherDataPro::GetChangedData() const
{
    return {
        .temperature = GetTemperature(),
        .humidity = GetHumidity(),
        .pressure = GetPressure(),
        .windSpeed = GetWindSpeed(),
        .windDirection = GetWindDirection(),
    };
}