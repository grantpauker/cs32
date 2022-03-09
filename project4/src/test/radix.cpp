#include "RadixTree.h"
#include <cassert>

int main()
{
    RadixTree<int> r;
    r.insert("abc", 0);
    r.insert("alo", 0);
    r.insert("aab", 0);
}
