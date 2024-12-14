#pragma once

#include <functional>
#include <iostream>

using DanceBehavior = std::function<void()>;

DanceBehavior CreateDanceMinuetBehavior();

DanceBehavior CreateDanceValseBehavior();

DanceBehavior CreateDanceNoWayBehavior();