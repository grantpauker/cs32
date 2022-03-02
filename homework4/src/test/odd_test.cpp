#include <algorithm>
#include <cassert>
#include <iostream>
#include <list>
#include <vector>

int a[8] = {2, 8, 5, 6, 7, 3, 4, 1};

#ifdef VECTOR
/*
 * Remove the odd integers from v.
 * It is acceptable if the order of the remaining even integers is not
 * the same as in the original vector.
 */
void removeOdd(std::vector<int> &v);

#include "oddvector.cpp"
std::vector<int> x(a, a + 8); // construct x from the array
#else
/*
 * Remove the odd integers from li.
 * It is acceptable if the order of the remaining even integers is not
 * the same as in the original list.
 */
void removeOdd(std::list<int> &li);

#include "oddlist.cpp"
std::list<int> x(a, a + 8); // construct x from the array
#endif

int main()
{
    assert(x.size() == 8 && x.front() == 2 && x.back() == 1);
    removeOdd(x);
    assert(x.size() == 4);
    std::vector<int> v(x.begin(), x.end()); // construct v from x
    sort(v.begin(), v.end());
    int expect[4] = {2, 4, 6, 8};
    for (int k = 0; k < 4; k++){
        assert(v[k] == expect[k]);
    }
    std::cout << "Passed" << std::endl;
}