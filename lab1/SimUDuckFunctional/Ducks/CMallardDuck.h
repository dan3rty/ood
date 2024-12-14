#pragma once

#include "CDuck.h"

class CMallardDuck : public CDuck
{
public:
    CMallardDuck();

    void Display() const override;
};