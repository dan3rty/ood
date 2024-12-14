add_executable(WeatherStation
        Observer/IObserver.h
        Observer/IObservable.h
        Observer/CObservable.hpp
        WeatherData/CWeatherData.h
        WeatherData/CWeatherData.cpp
        Displays/CurrentConditionsDisplay/CCurrentConditionsDisplay.h
        Displays/CurrentConditionsDisplay/CCurrentConditionsDisplay.cpp
        Displays/StatsDisplay/CStatsDisplay.h
        Displays/StatsDisplay/CStatsDisplay.cpp
        Displays/StatsDisplay/StatsMonitor/CStatsMonitor.h
        Displays/StatsDisplay/StatsMonitor/CStatsMonitor.cpp
        main.cpp)

add_subdirectory(tests)