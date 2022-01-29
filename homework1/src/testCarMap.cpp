#include <iostream>
#include <cassert>
#include "CarMap.h"

int main()
{
    CarMap cm;
    double d = -1;
    assert(cm.fleetSize() == 0);
    assert(cm.addCar("ABC") && cm.miles("ABC") == 0);
    assert(cm.addCar("XYZ") && cm.miles("XYZ") == 0);
    assert(cm.addCar("QRS") && cm.miles("QRS") == 0);
    assert(cm.fleetSize() == 3);
    assert(cm.miles("LMNO") == -1);
    assert(!cm.drive("LMNO", -1));
    assert(!cm.drive("ABC", -1));
    assert(cm.drive("ABC", 10) && cm.miles("ABC") == 10);
    assert(cm.drive("ABC", 20) && cm.miles("ABC") == 30);
    cm.print();

    std::cout << "Passed all tests" << std::endl;
}