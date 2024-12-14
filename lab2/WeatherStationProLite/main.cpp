#include <cstdlib>

#include "Displays/CurrentConditionsDisplay/CCurrentConditionsDisplay.h"
#include "Displays/FishermanDisplay/CFishermanDisplay.h"
#include "WeatherDataProLite/CWeatherDataProLite.h"

int main()
{
    CWeatherDataProLite wdProLite;

    CCurrentConditionsDisplay display;
    CFishermanDisplay fishermanDisplay;

    wdProLite.RegisterObserver(display, WeatherChangedEvent::All);
    wdProLite.RegisterObserver(fishermanDisplay, WeatherChangedEvent::Temperature);
    wdProLite.RegisterObserver(fishermanDisplay, WeatherChangedEvent::Pressure);

    wdProLite.SetMeasurements(3, 0.7, 760, 3, 90);
    wdProLite.SetMeasurements(3, 0.8, 760, 5, 300);

    wdProLite.RemoveObserver(display, WeatherChangedEvent::All);

    wdProLite.SetMeasurements(5, 0.8, 760, 5, 300);
    wdProLite.SetMeasurements(3, 0.8, 760, 5, 300);
    wdProLite.SetMeasurements(4, 0.8, 758, 5, 300);

    return EXIT_SUCCESS;
}