#include <iostream>
#include "CarMap.h"
#include "Map.h"

CarMap::CarMap() {}

bool CarMap::addCar(std::string license)
{
    return m_map.insert(license, 0);
}

double CarMap::miles(std::string license) const
{
    double distance = -1;
    m_map.get(license, distance);
    return distance;
}

bool CarMap::drive(std::string license, double distance)
{
    double cur_distance = miles(license);
    if (distance < 0 || cur_distance == -1)
    {
        return false;
    }
    m_map.update(license, cur_distance + distance);
    return true;
}

int CarMap::fleetSize() const
{
    return m_map.size();
}

void CarMap::print() const
{
    std::string license;
    double distance;
    for (int i = 0; i < m_map.size(); i++)
    {
        m_map.get(i, license, distance);
        std::cout << license << " " << distance << std::endl;
    }
}
