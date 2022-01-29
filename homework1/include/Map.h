#ifndef MAP_H
#define MAP_H
#include <string>

#define MAX(x, y) (x) > (y) ? (x) : (y)

using KeyType = std::string;
using ValueType = double;

const int DEFAULT_MAX_ITEMS = 260;

class Map
{
public:
  /*
   * Create an empty map (i.e., one with no key/value pairs)
   */
  Map();

  /*
   * Return true if the map is empty, otherwise false.
   */
  bool empty() const;

  /*
   * Return the number of key/value pairs in the map.
   */
  int size() const;

  /*
   * If key is not equal to any key currently in the map, and if the
   * key/value pair can be added to the map, then do so and return true.
   * Otherwise, make no change to the map and return false (indicating
   * that either the key is already in the map, or the map has a fixed
   * capacity and is full).
   */
  bool insert(const KeyType &key, const ValueType &value);

  /*
   * If key is equal to a key currently in the map, then make that key no
   * longer map to the value that it currently maps to, but instead map to
   * the value of the second parameter; return true in this case.
   * Otherwise, make no change to the map and return false.
   */
  bool update(const KeyType &key, const ValueType &value);

  /*
   * If key is equal to a key currently in the map, then make that key no
   * longer map to the value that it currently maps to, but instead map to
   * the value of the second parameter; return true in this case.
   * If key is not equal to any key currently in the map and if the
   * key/value pair can be added to the map, then do so and return true.
   * Otherwise, make no change to the map and return false (indicating
   * that the key is not already in the map and the map has a fixed
   * capacity and is full).
   */
  bool insertOrUpdate(const KeyType &key, const ValueType &value);

  /*
   * If key is equal to a key currently in the map, remove the key/value
   * pair with that key from the map and return true. Otherwise, make
   * no change to the map and return false.
   */
  bool erase(const KeyType &key);

  /*
   * Return true if key is equal to a key currently in the map, otherwise
   * false.
   */
  bool contains(const KeyType &key) const;

  /*
   * If key is equal to a key currently in the map, set value to the
   * value in the map which that key maps to, and return true. Otherwise,
   * make no change to the value parameter of this function and return
   * false.
   */
  bool get(const KeyType &key, ValueType &value) const;

  /*
   * If 0 <= i < size(), copy into the key and value parameters the
   * key and value of the key/value pair in the map whose key is strictly
   * greater than exactly i keys in the map and return true. Otherwise,
   * leave the key and value parameters unchanged and return false.
   */
  bool get(int i, KeyType &key, ValueType &value) const;

  /*
   * Exchange the contents of this map with the other one.
   */
  void swap(Map &other);

  /*
   * Dump data from the map to cerr.
   */
  void dump() const;

private:
  struct MapData
  {
    KeyType key;
    ValueType value;
  };

  MapData m_data[DEFAULT_MAX_ITEMS];
  int m_size;

  /*
   * If key is equal to a key currently in the map, return the index
   * of that key in the array. Otherwise, return -1.
   */
  int index(const KeyType &key) const;
};
#endif
