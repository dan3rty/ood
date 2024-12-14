#pragma once

#include "../Observer/CObservable.hpp"

struct WeatherInfo
{
    double temperature = 0;
    double humidity = 0;
    double pressure = 0;
};

class CWeatherData final : public CObservable<WeatherInfo>
{
public:
    [[nodiscard]] double GetTemperature() const;
    [[nodiscard]] double GetHumidity() const;
    [[nodiscard]] double GetPressure() const;

    void MeasurementsChanged();

    void SetMeasurements(double temperature, double humidity, double pressure);

protected:
    [[nodiscard]] WeatherInfo GetChangedData() const override;

private:
    double m_temperature = 0.0;
    double m_humidity = 0.0;
    double m_pressure = 760.0;
};