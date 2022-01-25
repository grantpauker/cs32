#include <iostream>
#include "newMap.h"

Map::Map() : Map(DEFAULT_MAX_ITEMS) {}

Map::Map(int max_size)
{
    m_size = 0;
    m_max_size = max_size;
    m_data = new MapData[m_max_size];
}

Map::~Map()
{
    delete[] m_data;
}

Map::Map(const Map &src)
{
    m_size = src.m_size;
    m_max_size = src.m_max_size;
    m_data = new MapData[m_max_size];
    for (int i = 0; i < m_size; i++)
    {
        m_data[i] = src.m_data[i];
    }
}

Map &Map::operator=(const Map &src)
{
    if (&src != this)
    {
        delete[] m_data;
        m_size = src.m_size;
        m_max_size = src.m_max_size;
        m_data = new MapData[m_max_size];
        for (int i = 0; i < m_size; i++)
        {
            m_data[i] = src.m_data[i];
        }
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
    if (m_size == m_max_size || contains(key))
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
    Map tmp = other;
    other = *this;
    *this = tmp;
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