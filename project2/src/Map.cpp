#include "Map.h"
#include <iostream>

Map::Map()
{
    dummy = new Node;
    dummy->next = nullptr;
    dummy->prev = nullptr;
    m_size = 0;
}

Map::Map(const Map &other)
{
    // initalize the member variables
    dummy = new Node;
    dummy->next = nullptr;
    dummy->prev = nullptr;
    m_size = other.m_size;
    // if the other list is empty, nothing needs to be done
    if (other.empty())
    {
        return;
    }
    Node *it = dummy;
    Node *it_other = other.dummy->next;
    // loop over the other until we hit the end
    while (it_other != nullptr)
    {
        // create a new node and copy the data from the current other node
        it->next = new Node;
        it->next->prev = it;
        it = it->next;
        it->key = it_other->key;
        it->value = it_other->value;
        it->next = nullptr;
        it_other = it_other->next;
    }
}

Map::~Map()
{
    Node *it = dummy;
    Node *next = nullptr;
    // loop over the list until we hit the end
    while (it != nullptr)
    {
        // store the next node we need to look at in a buffer and delete the current node
        next = it->next;
        delete it;
        it = next;
    }
}

Map &Map::operator=(const Map &other)
{
    // check for aliasing
    if (this == &other)
    {
        return *this;
    }
    Node *it = dummy;
    Node *next = nullptr;
    // loop over the list until we hit the end
    while (it != nullptr)
    {
        // store the next node we need to look at in a buffer and delete the current node
        next = it->next;
        delete it;
        it = next;
    }
    // initalize the member variables
    dummy = new Node;
    dummy->next = nullptr;
    dummy->prev = nullptr;
    m_size = other.m_size;
    // if the other list is empty, nothing needs to be done
    if (other.empty())
    {
        return *this;
    }
    it = dummy;
    Node *it_other = other.dummy->next;
    // loop over the other until we hit the end
    while (it_other != nullptr)
    {
        // create a new node and copy the data from the current other node
        it->next = new Node;
        it->next->prev = it;
        it = it->next;
        it->key = it_other->key;
        it->value = it_other->value;
        it->next = nullptr;
        it_other = it_other->next;
    }
    return *this;
}

bool Map::empty() const
{
    return m_size == 0;
}

int Map::size() const
{
    return m_size;
}

bool Map::insert(const KeyType &key, const ValueType &value)
{
    // call insertOrUpdate with insert true and update false
    return insertOrUpdate(key, value, true, false);
}

bool Map::update(const KeyType &key, const ValueType &value)
{
    // call insertOrUpdate with insert false and update true
    return insertOrUpdate(key, value, false, true);
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value)
{
    // call insertOrUpdate with insert true and update true
    insertOrUpdate(key, value, true, true);
    return true;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value, bool insert, bool update)
{
    Node *it = dummy;
    // loop overlist until we reach the end or we get to right before where key should be inserted
    while (it->next != nullptr && it->next->key <= key)
    {
        if (key == it->next->key)
        {
            if (update)
            {
                // if key is already in the map and we are allowed to update it, set value and return true
                it->next->value = value;
                return true;
            }
            // if key is already in the map and we aren't allowed to update it, return false
            return false;
        }
        it = it->next;
    }
    if (update && !insert)
    {
        // if the end of the map was reached and we expected to update something, return false
        return false;
    }
    // create and insert a new node
    Node *tmp = new Node;
    tmp->next = it->next;
    it->next = tmp;
    tmp->prev = it;
    tmp->key = key;
    tmp->value = value;
    m_size++;
    return true;
}

bool Map::erase(const KeyType &key)
{
    Node *it = dummy;
    // loop over list until we reach our index or we encounter the key we want
    while (it->next != nullptr && it->next->key != key)
    {
        it = it->next;
    }
    // if the end was reached and no key was found, return false
    if (it->next == nullptr)
    {
        return false;
    }
    // delete the found node and shift the list over
    Node *tmp = it->next->next;
    delete it->next;
    it->next = tmp;
    m_size--;
    return true;
}

bool Map::contains(const KeyType &key) const
{
    ValueType tmp;
    // use the get function to check if the node exists
    return get(key, tmp);
}

bool Map::get(const KeyType &key, ValueType &value) const
{
    Node *it = dummy->next;
    // loop over the linked list until we hit the end
    while (it != nullptr)
    {
        // if the current node has the desired key, get its value and return true
        if (it->key == key)
        {
            value = it->value;
            return true;
        }
        it = it->next;
    }
    // if we reached the end of the array and no node
    // with our desired key was found, return false
    return false;
}

bool Map::get(int i, KeyType &key, ValueType &value) const
{
    // ensure index is in range
    if (i < 0 || size() <= i)
    {
        return false;
    }
    int count = 0;
    Node *it = dummy->next;
    // loop over list until we reach our index or we hit the end
    while (it != nullptr && count != i)
    {
        count++;
        it = it->next;
    }
    // we are at the end of the list so set the returned values
    key = it->key;
    value = it->value;
    return true;
}

void Map::swap(Map &other)
{
    // use a temporary map to swap
    Map tmp = other;
    other = *this;
    *this = tmp;
}

void Map::dump() const
{
    Node *it = dummy->next;
    // loop over the list and print the keys and values
    while (it != nullptr)
    {
        std::cerr << it->key << ": " << it->value << std::endl;
        it = it->next;
    }
}

bool merge(const Map &m1, const Map &m2, Map &result)
{
    bool ret = true;
    // clear all the nodes in result
    result = Map(); 
    // loop over all the nodes of the first map
    for (int i = 0; i < m1.size(); i++)
    {
        // insert all the nodes from m1 into result
        KeyType key;
        ValueType value;
        m1.get(i, key, value);
        result.insert(key, value);
    }
    // loop over all the nodes of the second map
    for (int i = 0; i < m2.size(); i++)
    {
        KeyType key;
        ValueType value;
        m2.get(i, key, value);
        // try and insert the current node from the second map into the result
        if (!result.insert(key, value))
        {
            // the insert failed because the key already exists
            ValueType cur_value;
            result.get(key, cur_value);
            // check if the key in m1 maps doesnt map to the same value as in m2
            if (value != cur_value)
            {
                // erase keys that don't align and prepare to return false
                ret = false;
                result.erase(key);
            }
        }
    }
    return ret;
}

void reassign(const Map &m, Map &result)
{
    int left = 0;
    int right = m.size() - 1;
    // if the list has 0 or 1 nodes, no reassigment can be done
    if (m.size() <= 1)
    {
        result = m;
        return;
    }
    result = Map();
    // keep incrementing the left index and decrementing the right value until they cross
    while (left < right)
    {
        // get the keys/values and the left/right indices
        KeyType left_key;
        ValueType left_value;
        KeyType right_key;
        ValueType right_value;
        m.get(left, left_key, left_value);
        m.get(right, right_key, right_value);
        // swap the nth element from the front with the nth element from the back
        result.insert(left_key, right_value);
        result.insert(right_key, left_value);
        left++;
        right--;
    }
    if (left == right)
    {
        // if the list has an odd number of nodes, preform one final swap so the middle element is reassigned
        KeyType first_key;
        ValueType first_value;
        KeyType middle_key;
        ValueType middle_value;
        m.get(0, first_key, first_value);
        m.get(left, middle_key, middle_value);
        result.update(first_key, middle_value);
        result.insert(middle_key, first_value);
    }
}
