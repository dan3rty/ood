#pragma once

#include "Beverages/IBeverage.h"
class CCoffeeShop
{
public:
    void Start();

private:
    bool SelectBeverage();

    bool SelectCappuccino();
    bool SelectLatte();
    bool SelectMilkshake();
    bool SelectTea();

    bool SelectCondiment();

    bool AddChocolateCrumbs();
    bool AddChocolateSlices();
    bool AddCoconutFlakes();
    bool AddIceCubes();
    bool AddLemon();
    bool AddLiqueur();
    bool AddSyrup();

    IBeveragePtr m_beverage;
};