#include "CCappuccino.h"

CCappuccino::CCappuccino(const CoffeePortion portion)
    : CPortionedCoffee("Cappuccino", portion)
{
}

double CCappuccino::GetCost() const
{
    switch (GetPortion())
    {
        case CoffeePortion::Standard:
            return 80;
        case CoffeePortion::Double:
            return 120;
        default:
            return 0;
    }
}