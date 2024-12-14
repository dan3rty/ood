#include "CWeatherDataProLite.h"

double CWeatherDataProLite::GetTemperature() const
{
    return m_temperature;
}

double CWeatherDataProLite::GetHumidity() const
{
    return m_humidity;
}

double CWeatherDataProLite::GetPressure() const
{
    return m_pressure;
}

double CWeatherDataProLite::GetWindSpeed() const
{
    return m_windSpeed;
}

double CWeatherDataProLite::GetWindDirection() const
{
    return m_windDirection;
}

void CWeatherDataProLite::MeasurementsChanged()
{
    NotifyObservers();
}

void CWeatherDataProLite::SetMeasurements(double temperature, double humidity, double pressure, double windSpeed, double windDirection)
{
    SetCurrentEvents(temperature, humidity, pressure, windSpeed, windDirection);
    m_temperature = temperature;
    m_humidity = humidity;
    m_pressure = pressure;
    m_windSpeed = windSpeed;
    m_windDirection = windDirection;

    MeasurementsChanged();
}

WeatherInfo CWeatherDataProLite::GetChangedData() const
{
    return {
        .temperature = GetTemperature(),
        .humidity = GetHumidity(),
        .pressure = GetPressure(),
        .windSpeed = GetWindSpeed(),
        .windDirection = GetWindDirection(),
    };
}

std::set<WeatherChangedEvent> CWeatherDataProLite::GetCurrentEvents() const
{
    return m_currentEvents;
}

void CWeatherDataProLite::SetCurrentEvents(double temperature, double humidity, double pressure, double windSpeed, double windDirection)
{
    m_currentEvents.clear();

    if (temperature != m_temperature)
    {
        m_currentEvents.emplace(WeatherChangedEvent::Temperature);
    }
    if (humidity != m_humidity)
    {
        m_currentEvents.emplace(WeatherChangedEvent::Humidity);
    }
    if (pressure != m_pressure)
    {
        m_currentEvents.emplace(WeatherChangedEvent::Pressure);
    }
    if (windSpeed != m_windSpeed)
    {
        m_currentEvents.emplace(WeatherChangedEvent::WindSpeed);
    }
    if (windDirection != m_windDirection)
    {
        m_currentEvents.emplace(WeatherChangedEvent::WindDirection);
    }

    if (!m_currentEvents.empty())
    {
        m_currentEvents.emplace(WeatherChangedEvent::All);
    }
}