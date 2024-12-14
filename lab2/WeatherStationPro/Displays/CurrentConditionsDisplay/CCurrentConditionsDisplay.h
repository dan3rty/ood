#pragma once

#include "../../WeatherDataPro/CWeatherDataPro.h"

class CCurrentConditionsDisplay final : public IObserver<WeatherInfo>
{
private:
    void Update(WeatherInfo const& data) override;
};