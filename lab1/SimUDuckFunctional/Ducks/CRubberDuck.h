#pragma once

#include "CDuck.h"

class CRubberDuck : public CDuck
{
public:
    CRubberDuck();

    void Display() const override;
};