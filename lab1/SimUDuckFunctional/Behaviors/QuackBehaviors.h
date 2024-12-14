#pragma once

#include <functional>
#include <iostream>

using QuackBehavior = std::function<void()>;

QuackBehavior CreateQuackBehavior();

QuackBehavior CreateSqueakBehavior();

QuackBehavior CreateMuteQuackBehavior();