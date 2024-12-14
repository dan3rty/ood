#include "CCurrentConditionsDisplay.h"
#include <iostream>

void CCurrentConditionsDisplay::Update(WeatherInfo const& data)
{
    std::cout << "Current Temp " << data.temperature << "\n"
              << "Current Hum " << data.humidity << "\n"
              << "Current Pressure " << data.pressure << "\n"
              << "----------------" << std::endl;
}