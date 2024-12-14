#include "Displays/CurrentConditionsDisplay/CCurrentConditionsDisplay.h"
#include "Displays/StatsDisplay/CStatsDisplay.h"
#include "WeatherDataPro/CWeatherDataPro.h"

int main()
{
    CWeatherDataPro wdPro;

    CCurrentConditionsDisplay display;
    CStatsDisplay statsDisplay;

    wdPro.RegisterObserver(display);
    wdPro.RegisterObserver(statsDisplay);

    wdPro.SetMeasurements(3, 0.7, 760, 3, 90);
    wdPro.SetMeasurements(5, 0.8, 761, 5, 300);

    return EXIT_SUCCESS;
}