#pragma once

#include "../../WeatherData/CWeatherData.h"

class CCurrentConditionsDisplay final : public IObserver<WeatherInfo>
{
private:
    void Update(WeatherInfo const& data) override;
};