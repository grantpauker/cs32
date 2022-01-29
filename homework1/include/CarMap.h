#ifndef CARMAP_H
#define CARMAP_H
#include "Map.h"

class CarMap
{
public:
  /*
   * Create an empty car map.
   */
  CarMap();

  /*
   * If a car with the given license plate is not currently in the map,
   * and there is room in the map, add an entry for that car recording
   * that it has been driven 0 miles, and return true. Otherwise,
   * make no change to the map and return false.
   */
  bool addCar(std::string license);

  /*
   * If a car with the given license plate is in the map, return how
   * many miles it has been driven; otherwise, return -1.
   */
  double miles(std::string license) const;

  /*
   * If no car with the given license plate is in the map or if
   * distance is negative, make no change to the map and return
   * false. Otherwise, increase by the distance parameter the number
   * of miles the indicated car has been driven and return true.
   */
  bool drive(std::string license, double distance);

  /*
   * Return the number of cars in the CarMap.
   */
  int fleetSize() const;

  /*
   * Write to cout one line for every car in the map. Each line
   * consists of the car's license plate, followed by one space,
   * followed by the number of miles that car has been driven. Write
   * no other text. The lines need not be in any particular order.
   */
  void print() const;

private:
  Map m_map;
};
#endif