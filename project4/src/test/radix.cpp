#include "RadixTree.h"
#include <cassert>
#include <iostream>
#include <vector>

int main()
{
    RadixTree<int> r;
    std::vector<std::string> v = {
        "romane",
        "romanus",
        "romulus",
        "rubens",
        "ruber",
        "rubicon",
        "rubicundus",
        "roman",
        "romper"};
    for (int i = 0; i < v.size(); i++)
    {
        r.insert(v[i], i);
    }
    // r.print();
    for (int i = 0; i < v.size(); i++)
    {
        std::string word = v[i];
        int *value = r.search(word);
        std::cout << word << ": " << std::flush << *value << std::endl;
        assert(*value == i);
    }
}
