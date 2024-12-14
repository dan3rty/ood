#pragma once

#include "IObservable.h"
#include <map>
#include <set>

template <typename T, typename Event>
class CObservable : public IObservable<T, Event>
{
public:
    using ObserverType = IObserver<T>;

    void RegisterObserver(ObserverType& observer, Event event) override
    {
        m_observers.emplace(event, &observer);
    }

    // нужно посылать какой именно ивент в нотифай
    void NotifyObservers() override
    {
        auto data = GetChangedData();
        auto events = GetCurrentEvents();
        auto observersCopy = m_observers;
        std::set<ObserverType*> updatedObservers;

        for (auto& [event, observer] : observersCopy)
        {
            if (events.contains(event) && !updatedObservers.contains(observer))
            {
                observer->Update(data);
                updatedObservers.insert(observer);
            }
        }
    }

    void RemoveObserver(ObserverType& observer, Event event) override
    {
        auto matchingObservers = m_observers.equal_range(event);
        for (auto it = matchingObservers.first; it != matchingObservers.second; ++it)
        {
            if (it->second == &observer)
            {
                m_observers.erase(it);
                break;
            }
        }
    }

protected:
    virtual T GetChangedData() const = 0;
    virtual std::set<Event> GetCurrentEvents() const = 0;

private:
    std::multimap<Event, ObserverType*> m_observers;
};