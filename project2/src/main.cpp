#include <iostream>
#include <cassert>
#include "Map.h"

bool testReassign(Map m, Map result)
{
    // ensure sizes are the same
    bool valid = m.size() == result.size();
    // loop over m
    for (int i = 0; i < m.size(); i++)
    {
        KeyType k;
        ValueType v;
        m.get(i, k, v);
        ValueType v_result;
        result.get(k, v_result);
        valid = valid && v != v_result; // ensures values are different in m and result
    }
    return valid;
}

int main()
{
    // default constructor
    Map m0;

    // EMPTY MAP:
    assert(m0.empty());            // test map is empty
    assert(m0.size() == 0);        // test size is 0
    assert(!m0.erase("pop"));      // test erase
    assert(!m0.update("pop", -1)); // test update

    // test insert (all keys are valid)
    KeyType k = "pop";
    ValueType v = -999.9;
    assert(m0.insert(k, v));
    assert(m0.insert("abc", 0));
    assert(m0.insert("bcd", 2));
    assert(m0.insert("zzz", 6));
    assert(m0.insert("cde", 3));
    assert(m0.insert("aabc", 1));
    assert(m0.insert("z", 5));
    assert(m0.insert("xyz", 4));

    // ensure duplicates aren't inserted
    assert(!m0.insert("abc", -1));
    assert(!m0.insert("xyz", -2));
    assert(!m0.insert("zzz", -3));

    KeyType k1 = "NULL";
    ValueType v1 = -999.9;
    assert(!m0.get("test", v1) && v1 == -999.9);                                               // test get with non existing key
    assert(!m0.get(-1, k1, v1) && !m0.get(m0.size(), k1, v1) && k1 == "NULL" && v1 == -999.9); // test get with invalid i parameter
    assert(m0.get("abc", v1) && v1 == 0);                                                      // test get with existing key

    // test get with valid indices
    m0.get(0, k1, v1);
    assert(m0.get(0, k1, v1) && k1 == "aabc" && v1 == 1);
    assert(m0.get(3, k1, v1) && k1 == "cde" && v1 == 3);
    assert(m0.get(7, k1, v1) && k1 == "zzz" && v1 == 6);

    assert(!m0.update("test", -1)); // test update with non existing key

    // test update with existing keys
    assert(m0.update(k, 14) && m0.get(k, v1) && v1 == 14);
    assert(m0.update("xyz", -4) && m0.get("xyz", v1) && v1 == -4);                             

    assert(m0.insertOrUpdate("xyz", 4) && m0.get("xyz", v1) && v1 == 4 && m0.size() == 8);     // test insertOrUpdate with existing key
    assert(m0.insertOrUpdate("frog", 17) && m0.get("frog", v1) && v1 == 17 && m0.size() == 9); // test insertOrUpdate with new key
    assert(m0.erase("frog") && !m0.contains("frog") && m0.size() == 8);                        // test erase with existing key

    // test contains with existing keys
    assert(m0.contains("cde"));
    assert(m0.contains("xyz"));

    assert(!m0.empty() && m0.size() == 8);                                      // test empty and size of non empty array
    assert(m0.contains(k) && m0.erase(k) && !m0.contains(k) && m0.size() == 7); // test erase with existing key
    assert(!m0.erase(k));                                                       // test erase with non existing key

    // test erase with more existing keys
    assert(m0.erase("cde") && m0.erase("xyz"));
    assert(!m0.contains("cde") && !m0.contains("xyz") && m0.size() == 5);

    Map m1;
    bool inserts = true;
    int m1_size = 300;
    // insert 300 values into m1
    for (int i = 0; i < m1_size; i++)
    {
        inserts = inserts && m1.insert("data" + std::to_string(i + 100), i + 100);
    }
    // assure all inserts were successful
    assert(inserts);
    assert(m1.size() == m1_size);

    Map m2;
    m2.insert("a", 0);
    m2.insert("b", 1);
    m2.insert("c", 2);

    int m1_init_size = m1.size();
    int m2_init_size = m2.size();

    m2.swap(m1);
    assert(m2.size() == m1_init_size && m1.size() == m2_init_size); // test swap sizes

    KeyType k2;
    ValueType v2;
    bool m2_values = true;
    // loop over m2 to ensure its pairs match that of m1
    for (int i = 0; i < m2.size(); i++)
    {
        m2_values = m2_values && m2.get(i, k2, v2) && k2 == "data" + std::to_string(i + 100) && v2 == i + 100;
    }
    assert(m2_values); // assert the m2 pairs are correct

    // assert the m1 pairs are correct
    assert(m1.get(0, k2, v2) && k2 == "a" && v2 == 0);
    assert(m1.get(1, k2, v2) && k2 == "b" && v2 == 1);
    assert(m1.get(2, k2, v2) && k2 == "c" && v2 == 2);

    Map *m3 = new Map(m0); // set m3 to m0 using copy constructor
    KeyType k3a;
    ValueType v3a;
    KeyType k3b;
    ValueType v3b;
    bool m3_values = true;

    // TEST COPY CONSTRUCTOR
    // loop over m0 to ensure its pairs match that of m3
    for (int i = 0; i < m0.size(); i++)
    {
        m3_values = m3_values && m0.get(i, k3a, v3a) && m3->get(i, k3b, v3b);
        m3_values = m3_values && k3a == k3b && v3a == v3b;
    }
    assert(m3_values); // assert m3 pairs are correct

    // TEST ASSIGNMENT OPERATOR
    *m3 = m0; // set m3 to m0 using assignment operator
    // loop over m0 to ensure its pairs match that of m3
    for (int i = 0; i < m0.size(); i++)
    {
        m3_values = m3_values && m0.get(i, k3a, v3a) && m3->get(i, k3b, v3b);
        m3_values = m3_values && k3a == k3b && v3a == v3b;
    }
    assert(m3_values); // assert m3 pairs are correct

    // TEST DECONSTRUCTOR
    delete m3; // delete m3
    // loop over m0 to ensure the deletion of m3 had no effect on m0
    for (int i = 0; i < m0.size(); i++)
    {
        m3_values = m3_values && m0.get(i, k3a, v3a);
    }
    assert(m3_values); // assert m0 pairs still exist

    Map m5;
    int m5_size = 9;
    // insert 9 values into m1
    for (int i = 0; i < m5_size; i++)
    {
        inserts = inserts && m5.insert("data" + std::to_string(i), i);
    }

    Map m6;
    reassign(m5, m6);             // reassigns m5 into m6
    assert(testReassign(m5, m6)); // test reassign

    Map m7;
    m7.insert("dog", 0);
    m7.insert("cat", 1);
    m7.insert("frog", 2);
    m7.insert("worm", 3);

    Map m8;
    m8.insert("bird", 4);
    m8.insert("bear", 5);
    m8.insert("ant", 6);
    m8.insert("toad", 7);

    Map m9;
    assert(merge(m7, m8, m9) && m9.size() == m7.size() + m8.size()); // test merge with no overlaps

    // test merge with overlap that has same value in both m7 and m8
    m7.insert("bird", 4);
    assert(merge(m7, m8, m9) && m9.size() == m7.size() + m8.size() - 1);

    // test merge with overlap that has different values in m7 and m8
    m7.insert("bear", -999);
    assert(!merge(m7, m8, m9) && m9.size() == m7.size() + m8.size() - 3);
    std::cerr << "Passed all tests" << std::endl;
}