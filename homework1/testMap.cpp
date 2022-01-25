#include <iostream>
#include <cassert>
#include "Map.h"

int main()
{
    Map m0;
    assert(m0.empty());

    KeyType k = "pop";
    ValueType v = -999.9;
    assert(m0.insert(k, v));
    assert(m0.insert("abc", 0));
    assert(m0.insert("aabc", 1));
    assert(m0.insert("bcd", 2));
    assert(m0.insert("cde", 3));
    assert(m0.insert("xyz", 4));
    assert(m0.insert("z", 5));
    assert(m0.insert("zzz", 6));
    assert(!m0.insert("abc", -1));
    assert(!m0.insert("xyz", -2));
    assert(!m0.insert("zzz", -3));

    KeyType k1 = "NULL";
    ValueType v1 = -999.9;
    assert(!m0.get("test", v1) && v1 == -999.9);
    assert(!m0.get(-1, k1, v1) && !m0.get(m0.size(), k1, v1) && k1 == "NULL" && v1 == -999.9);
    assert(m0.get("abc", v1) && v1 == 0);
    assert(m0.get(3, k1, v1) && k1 == "cde" && v1 == 3);
    assert(m0.get(7, k1, v1) && k1 == "zzz" && v1 == 6);

    assert(!m0.update("test", -1));
    assert(m0.update(k, 14) && m0.get(k, v1) && v1 == 14);
    assert(m0.update("xyz", -4) && m0.get("xyz", v1) && v1 == -4);
    assert(m0.insertOrUpdate("xyz", 4) && m0.get("xyz", v1) && v1 == 4 && m0.size() == 8);
    assert(m0.insertOrUpdate("frog", 17) && m0.get("frog", v1) && v1 == 17 && m0.size() == 9);
    assert(m0.erase("frog") && !m0.contains("frog") && m0.size() == 8);

    assert(m0.contains("cde") && m0.contains("xyz"));
    assert(!m0.empty() && m0.size() == 8);
    assert(m0.contains(k) && m0.erase(k) && !m0.contains(k) && m0.size() == 7);
    assert(!m0.erase(k));
    assert(m0.erase("cde") && m0.erase("xyz"));
    assert(!m0.contains("cde") && !m0.contains("xyz") && m0.size() == 5);

    Map m1;
    bool inserts = true;
    for (int i = 0; i < DEFAULT_MAX_ITEMS; i++)
    {
        inserts = inserts && m1.insert("data" + std::to_string(i + 100), i + 100);
    }
    assert(inserts);
    assert(!m1.insert("anything", -19));
    assert(!m1.insertOrUpdate("anything", -19));
    assert(m1.size() == DEFAULT_MAX_ITEMS);

    Map m2;
    m2.insert("a", 0);
    m2.insert("b", 1);
    int m1_init_size = m1.size();
    int m2_init_size = m2.size();
    m2.swap(m1);
    assert(m2.size() == m1_init_size && m1.size() == m2_init_size);
    KeyType k2;
    ValueType v2;
    bool m2_values = true;
    for (int i = 0; i < m2.size(); i++)
    {
        m2_values = m2_values && m2.get(i, k2, v2) && k2 == "data" + std::to_string(i + 100) && v2 == i + 100;
    }
    assert(m2_values);
    assert(m1.get(0, k2, v2) && k2 == "a" && v2 == 0);
    assert(m1.get(1, k2, v2) && k2 == "b" && v2 == 1);
    std::cout << "Passed all tests" << std::endl;
}