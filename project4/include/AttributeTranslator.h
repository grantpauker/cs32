#ifndef ATTRIBUTE_TRANSLATOR_H
#define ATTRIBUTE_TRANSLATOR_H
#include "RadixTree.h"
#include "provided.h"
#include <string>
#include <vector>

class AttributeTranslator
{
public:
    AttributeTranslator() {}
    ~AttributeTranslator() {}

    bool Load(std::string filename);
    std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair &source) const;

private:
    RadixTree<std::vector<AttValPair>> m_translator;
};
#endif
