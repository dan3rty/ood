#include "CWeatherDataPro.h"

double CWeatherDataPro::GetWindSpeed() const
{
    return m_windSpeed;
}

double CWeatherDataPro::GetWindDirection() const
{
    return m_windDirection;
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
        .windInfo = { {
            .speed = GetWindSpeed(),
            .direction = GetWindDirection(),
        } },
    };
}