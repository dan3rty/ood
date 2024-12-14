#pragma once

#include "../../WeatherDataProLite/CWeatherDataProLite.h"

class CFishermanDisplay final : public IObserver<WeatherInfo>
{
private:
    void Update(WeatherInfo const& data) override;
};