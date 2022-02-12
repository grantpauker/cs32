#include "Map.h"
#include <iostream>
#include <string>
#include <cassert>

int main()
{
    Map<int, double> mid;
    Map<std::string, int> msi;
    assert(msi.empty());
    assert(msi.size() == 0);
    assert(msi.insert("Hello", 10));
    assert(mid.insert(10, 3.5));
    assert(msi.update("Hello", 20));
    assert(mid.update(10, 4.75));
    assert(msi.insertOrUpdate("Goodbye", 30));
    assert(msi.erase("Goodbye"));
    assert(mid.contains(10));
    int k;
    assert(msi.get("Hello", k));
    std::string s;
    assert(msi.get(0, s, k));
    Map<std::string, int> msi2(msi);
    msi2.swap(msi);
    msi2 = msi;
    merge(msi, msi2, msi);
    merge(mid, mid, mid);
    reassign(msi, msi2);
    reassign(mid, mid);
    std::cout << "Passed all tests" << std::endl;
}