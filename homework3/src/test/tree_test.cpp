#include <iostream>
#include <cassert>

#include "tree.cpp"

void print(double a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}
bool isSorted(double a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        if (a[i] > a[i - 1])
        {
            return false;
        }
    }
    return true;
}

bool testOrder(double a[], int n)
{
    order(a, n);
    return isSorted(a, n);
}

int main()
{
    double a1[] = {10, 50, 40, 20, 50, 40, 30};
    double a2_a[] = {10, 20, 40};
    double a2_b[] = {10, 40, 30};
    double a2_c[] = {20, 10, 40};
    double a2_d[] = {50, 40, 30};
    assert(countContains(a1, 7, a2_a, 3) == 1);
    assert(countContains(a1, 7, a2_b, 3) == 2);
    assert(countContains(a1, 7, a2_c, 3) == 0);
    assert(countContains(a1, 7, a2_d, 3) == 3);

    double b1[] = {17, 34, -8, 1, 0, 100, 22};
    double b2[] = {0, 0, 0, 0, 0, 0, 0, 0};
    assert(testOrder(b1, 3));
    assert(testOrder(b1, 7));
    assert(testOrder(b2, 7));
    assert(testOrder(b1, 0));
}