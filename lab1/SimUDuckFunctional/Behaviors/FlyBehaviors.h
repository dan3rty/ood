#pragma once

#include <functional>

using FlyBehavior = std::function<int()>;

FlyBehavior CreateFlyWithWingsBehavior();

FlyBehavior CreateFlyNoWayBehavior();