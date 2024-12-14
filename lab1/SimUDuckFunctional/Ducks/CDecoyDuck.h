#pragma once

#include "CDuck.h"

class CDecoyDuck : public CDuck
{
public:
    CDecoyDuck();

    void Display() const override;
};