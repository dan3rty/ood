#include "CDuck.h"
#include <cassert>

CDuck::CDuck(
    QuackBehavior&& quackBehavior,
    FlyBehavior&& flyBehavior,
    DanceBehavior&& danceBehavior)
    : m_quackBehavior(std::move(quackBehavior))
    , m_flyBehavior(std::move(flyBehavior))
    , m_danceBehavior(std::move(danceBehavior))
{
}

void CDuck::Quack()
{
    m_quackBehavior();
}

void CDuck::Fly()
{
    if (m_flyBehavior)
    {
        // крякать до полёта
        if (m_flyBehavior() % 2 == 0)
        {
            m_quackBehavior();
        }
    }
}

void CDuck::Dance()
{
    m_danceBehavior();
}

void CDuck::SetFlyBehavior(FlyBehavior && flyBehavior)
{
    assert(flyBehavior);
    m_flyBehavior = std::move(flyBehavior);
}