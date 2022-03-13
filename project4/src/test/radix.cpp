#include "RadixTree.h"
#include <cassert>

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
    r.print();
    for (int i = 0; i < v.size(); i++)
    {
        std::cout << v[i] << ": " << std::flush << *r.search(v[i]) << std::endl;
    }
}
