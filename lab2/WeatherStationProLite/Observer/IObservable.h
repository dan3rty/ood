#pragma once

#include "IObserver.h"

template <typename T, typename Event>
class IObservable
{
public:
    virtual void RegisterObserver(IObserver<T>& observer, Event event) = 0;
    virtual void NotifyObservers() = 0;
    virtual void RemoveObserver(IObserver<T>& observer, Event event) = 0;

    virtual ~IObservable() = default;
};