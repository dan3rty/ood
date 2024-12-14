#pragma once

#include "../Behaviors/DanceBehaviors.h"
#include "../Behaviors/FlyBehaviors.h"
#include "../Behaviors/QuackBehaviors.h"

class CDuck
{
public:
    CDuck(
        QuackBehavior&& quackBehavior,
        FlyBehavior&& flyBehavior,
        DanceBehavior&& danceBehavior);

    void Quack();
    void Fly();
    void Dance();

    void SetFlyBehavior(FlyBehavior&& flyBehavior);

    virtual void Display() const = 0;

    virtual ~CDuck() = default;

private:
    QuackBehavior m_quackBehavior;
    FlyBehavior m_flyBehavior;
    DanceBehavior m_danceBehavior;
};