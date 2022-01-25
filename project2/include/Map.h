#ifndef MAP_H
#define MAP_H
#include <string>

using KeyType = std::string;
using ValueType = double;

class Map
{
public:
  /*
   * Create an empty map (i.e., one with no key/value pairs)
   */
  Map();

  /*
   * Creates a new map from another map
   */
  Map(const Map &other);

  /*
   * Destroys the map and deallocates the nodes
   */
  ~Map();

  /*
   * Duplicates one map into an already existing map
   */
  Map &operator=(const Map &other);

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
   * that either the key is already in the map).
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
   * If key is not equal to any key currently in the map, then add the
   * key/value pair to the map and return true.
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
  struct Node
  {
    Node *next;
    Node *prev;
    KeyType key;
    ValueType value;
  };

  Node *dummy;
  int m_size;

  bool insertOrUpdate(const KeyType &key, const ValueType &value, bool insert, bool update);
};

/*
 * Merges two maps accourding to the following rules: If a key appears in
 * exactly one of m1 and m2, then result contains a pair consisting of
 * that key and its corresponding value. If a key appears in both m1 and m2,
 * with the same corresponding value in both, then result contains exactly
 * one pair with that key and value. If there exists a key that appears in
 * both m1 and m2, but with different corresponding values, then this function
 * returns false; if there is no key like this, the function returns true.
 */
bool merge(const Map &m1, const Map &m2, Map &result);

/*
 * Shuffles a map to ensure that each key maps to a new value.
 */
void reassign(const Map &m, Map &result);
#endif
