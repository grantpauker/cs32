#include <iostream>
#include "Map.h"

Map::Map()
{
    m_size = 0;
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
    if (m_size == DEFAULT_MAX_ITEMS || contains(key))
    {
        return false;
    }
    MapData new_data;
    new_data.key = key;
    new_data.value = value;
    m_data[m_size] = new_data;
    m_size++;
    return true;
}

bool Map::update(const KeyType &key, const ValueType &value)
{
    int i = index(key);
    if (i == -1)
    {
        return false;
    }
    m_data[i].value = value;
    return true;
}

bool Map::insertOrUpdate(const KeyType &key, const ValueType &value)
{
    if (contains(key))
    {
        update(key, value);
        return true;
    }
    return insert(key, value);
}

bool Map::erase(const KeyType &key)
{
    int i = index(key);
    if (i == -1)
    {
        return false;
    }
    for (int j = i; j < size() - 1; j++)
    {
        m_data[j] = m_data[j + 1];
    }
    m_size--;
    return true;
}

bool Map::contains(const KeyType &key) const
{
    return index(key) != -1;
}

bool Map::get(const KeyType &key, ValueType &value) const
{
    for (int i = 0; i < size(); i++)
    {
        if (m_data[i].key == key)
        {
            value = m_data[i].value;
            return true;
        }
    }
    return false;
}

bool Map::get(int i, KeyType &key, ValueType &value) const
{
    if (i < 0 || size() <= i)
    {
        return false;
    }
    for (int j = 0; j < size(); j++)
    {
        int n = 0;
        for (int k = 0; k < size(); k++)
        {
            if (m_data[j].key > m_data[k].key)
            {
                n++;
            }
        }
        if (n == i)
        {
            key = m_data[j].key;
            value = m_data[j].value;
            break;
        }
    }
    return true;
}

void Map::swap(Map &other)
{
    int max_size = MAX(m_size, other.m_size);
    for (int i = 0; i < max_size; i++)
    {
        MapData tmp = m_data[i];
        m_data[i] = other.m_data[i];
        other.m_data[i] = tmp;
    }
    int tmp = m_size;
    m_size = other.m_size;
    other.m_size = tmp;
}

int Map::index(const KeyType &key) const
{
    for (int i = 0; i < size(); i++)
    {
        if (m_data[i].key == key)
        {
            return i;
        }
    }
    return -1;
}

void Map::dump() const
{
    KeyType key;
    ValueType value;
    for (int i = 0; i < size(); i++)
    {
        get(i, key, value);
        std::cerr << key << ": " << value << std::endl;
    }
}
