#ifndef RADIX_TREE_H
#define RADIX_TREE_H
#include <map> 
#include <string>

// TODO implement
template <typename ValueType>
class RadixTree
{
public:
  RadixTree()
  {
    m_map = new std::map<std::string, ValueType>();
  }
  ~RadixTree()
  {
    delete m_map;
  }

  void insert(std::string key, /* TODO const */ ValueType &value)
  {
    std::pair<std::string, ValueType> p(key, value);
    m_map->insert(p);
  }
  ValueType *search(std::string key) const
  {
    auto it = m_map->find(key);
    if (it == m_map->end())
    {
      return nullptr;
    }
    return &(it->second);
  }

private:
  std::map<std::string, ValueType> *m_map;
};
#endif