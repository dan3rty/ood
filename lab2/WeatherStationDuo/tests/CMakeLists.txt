add_executable(WeatherStationDuoTest
        ../Observer/IObserver.h
        ../Observer/IObservable.h
        ../Observer/CObservable.hpp
        ../WeatherData/CWeatherData.h
        ../WeatherData/CWeatherData.cpp
        WeatherStationDuo_tests.cpp)

target_link_libraries(WeatherStationDuoTest PUBLIC catch2)
add_test(NAME WeatherStationDuoTest COMMAND WeatherStationDuoTest)