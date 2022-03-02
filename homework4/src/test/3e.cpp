#include <iostream>
#include <list>
#include <vector>
const int MAGIC = 11223344;

void test()
{
    bool allValid = true;

    std::vector<int> v1(5, MAGIC);
    int k = 0;
    for (; k != v1.size(); k++)
    {
        if (v1[k] != MAGIC)
        {
            std::cout << "v1[" << k << "] is " << v1[k] << ", not " << MAGIC << "!" << std::endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                v1.push_back(MAGIC);
        }
    }
    if (allValid && k == 10)
        std::cout << "Passed test 1" << std::endl;
    else
        std::cout << "Failed test 1" << std::endl;

    allValid = true;
    std::list<int> l1(5, MAGIC);
    k = 0;
    for (auto p = l1.begin(); p != l1.end(); p++, k++)
    {
        if (*p != MAGIC)
        {
            std::cout << "Item# " << k << " is " << *p << ", not " << MAGIC << "!" << std::endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                l1.push_back(MAGIC);
        }
    }
    if (allValid && k == 10)
        std::cout << "Passed test 2" << std::endl;
    else
        std::cout << "Failed test 2" << std::endl;

    allValid = true;
    std::vector<int> v2(5, MAGIC);
    k = 0;
    for (auto p = v2.begin(); p != v2.end(); p++, k++)
    {
        if (k >= 20) // prevent infinite loop
            break;
        if (*p != MAGIC)
        {
            std::cout << "Item# " << k << " is " << *p << ", not " << MAGIC << "!" << std::endl;
            allValid = false;
        }
        if (k == 2)
        {
            for (int i = 0; i < 5; i++)
                v2.push_back(MAGIC);
        }
    }
    if (allValid && k == 10)
        std::cout << "Passed test 3" << std::endl;
    else
        std::cout << "Failed test 3" << std::endl;
}

int main()
{
    test();
}
