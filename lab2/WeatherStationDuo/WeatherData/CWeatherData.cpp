
#include "CWeatherData.h"

double CWeatherData::GetTemperature() const
{
    return m_temperature;
}

double CWeatherData::GetHumidity() const
{
    return m_humidity;
}

double CWeatherData::GetPressure() const
{
    return m_pressure;
}

void CWeatherData::MeasurementsChanged()
{
    NotifyObservers();
}

void CWeatherData::SetMeasurements(double temperature, double humidity, double pressure)
{
    m_temperature = temperature;
    m_humidity = humidity;
    m_pressure = pressure;

    MeasurementsChanged();
}

WeatherInfo CWeatherData::GetChangedData() const
{
    return {
        .temperature = GetTemperature(),
        .humidity = GetHumidity(),
        .pressure = GetPressure(),
    };
}
