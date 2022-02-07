#include <iostream>
#include <cassert>
bool somePredicate(double x)
{
    return x < 0;
}

#include "linear.cpp"

int main()
{
    double a1[] = {-1, -1, -1, -1, -1, -1, 0};
    double a2[] = {-1, -1, -1, 0, -1, -1, -1};
    double a3[] = {0, -1, 0, -1, -1, -1, 0};
    double a4[] = {-1, -1, -1, -1, -1, -1, -1};
    assert(anyFalse(a1, 7));
    assert(anyFalse(a2, 7));
    assert(anyFalse(a3, 7));
    assert(!anyFalse(a4, 7));
    assert(!anyFalse(a1, 0));

    assert(countFalse(a1, 7) == 1);
    assert(countFalse(a2, 7) == 1);
    assert(countFalse(a3, 7) == 3);
    assert(countFalse(a3, 3) == 2);
    assert(countFalse(a4, 7) == 0);
    assert(countFalse(a1, 0) == 0);

    double b1[] = {0, 0, 0, -1, 0, 0, 0};
    double b2[] = {0, 0, 0, -1, -1, 0, 0};
    double b3[] = {-1, 0, 0, 0, 0, 0, 0};
    double b4[] = {0, 0, 0, 0, 0, 0, 0};
    assert(firstTrue(b1, 7) == 3);
    assert(firstTrue(b2, 7) == 3);
    assert(firstTrue(b3, 7) == 0);
    assert(firstTrue(b4, 7) == -1);
    assert(firstTrue(b1, 3) == -1);

    double c1[] = {17, 34, -8, 1, 0, 100, 22};
    double c2[] = {100, 34, -8, 1, 0, 100, 22};
    double c3[] = {0, 0, 0, 0, 0, 0, 0};
    assert(locateMax(c1, 7) == 5);
    assert(locateMax(c1, 5) == 1);
    assert(locateMax(c2, 7) == 0);
    assert(locateMax(c3, 7) == 0);
    assert(locateMax(c1, 0) == -1);

    double d1[] = {10, 50, 40, 20, 50, 40, 30};
    double d2a[] = {50, 20, 30};
    double d2b[] = {50, 40, 40};
    double d2c[] = {50, 30, 20};
    double d2d[] = {10, 20, 20};
    assert(contains(d1, 7, d2a, 3));
    assert(contains(d1, 7, d2b, 3));
    assert(!contains(d1, 7, d2c, 3));
    assert(!contains(d1, 7, d2d, 3));
}