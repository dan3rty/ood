#include "CFishermanDisplay.h"
#include <iostream>

void CFishermanDisplay::Update(WeatherInfo const& data)
{
    std::cout << "Current Temp " << data.temperature << "\n"
              << "Current Pressure " << data.pressure << "\n"
              << "----------------" << std::endl;
}