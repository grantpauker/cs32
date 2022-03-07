#ifndef ATTRIBUTE_TRANSLATOR_H
#define ATTRIBUTE_TRANSLATOR_H
#include "RadixTree.h"
#include "provided.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
class AttributeTranslator
{
public:
    AttributeTranslator() {}

    ~AttributeTranslator() {}

    bool Load(std::string filename)
    {
        std::ifstream file;
        file.open(filename);
        std::string line;
        while (std::getline(file, line))
        {
            std::string att, val;
            std::stringstream str(line);
            std::getline(str, att, ',');
            std::getline(str, val, ',');
            AttValPair source(att, val);
            std::getline(str, att, ',');
            std::getline(str, val, ',');
            AttValPair compatible(att, val);
            std::string source_str = source.attribute + "," + source.value;
            std::vector<AttValPair> **matching_avps = m_translator.search(source_str);
            if (matching_avps == nullptr)
            {
                std::vector<AttValPair> *v = new std::vector<AttValPair>();
                v->push_back(compatible);
                m_translator.insert(source_str, v);
            }
            else
            {
                (*matching_avps)->push_back(compatible);
            }
        }
        return true;
    }
    std::vector<AttValPair> FindCompatibleAttValPairs(
        const AttValPair &source) const
    {
        std::vector<AttValPair> **avps = m_translator.search(source.attribute+","+source.value);
        if(avps == nullptr){
            return std::vector<AttValPair>();
        }
        return **avps;
    }

private:
    RadixTree<std::vector<AttValPair> *> m_translator;
};
#endif
