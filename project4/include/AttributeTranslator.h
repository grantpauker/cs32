#ifndef ATTRIBUTE_TRANSLATOR_H
#define ATTRIBUTE_TRANSLATOR_H
#include "provided.h"
#include <string>
#include <vector>
class AttributeTranslator
{
public:
    AttributeTranslator() {}

    ~AttributeTranslator() {}

    bool Load(std::string filename) { return false; }
    std::vector<AttValPair> FindCompatibleAttValPairs(
        const AttValPair &source) const
    {
        std::vector<AttValPair> v;
        return v;
    }
};
#endif
