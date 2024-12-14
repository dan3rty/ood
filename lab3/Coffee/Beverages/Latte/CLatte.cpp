#include "CLatte.h"

CLatte::CLatte(const CoffeePortion portion)
    : CPortionedCoffee("Latte", portion)
{
}

double CLatte::GetCost() const
{
    switch (GetPortion())
    {
        case CoffeePortion::Standard:
            return 90;
        case CoffeePortion::Double:
            return 130;
        default:
            return 0;
    }
}