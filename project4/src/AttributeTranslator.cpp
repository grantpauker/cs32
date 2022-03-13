#include "AttributeTranslator.h"
#include "RadixTree.h"
#include "provided.h"
#include <fstream>
#include <list>
#include <sstream>
#include <string>
#include <vector>

AttributeTranslator::~AttributeTranslator()
{
    int i = 0; 
    for (auto source : m_sources)
    {
        std::vector<AttValPair> **compatible = m_translator.search(source);
        if (compatible != nullptr)
        {
            i++;
            delete *compatible;
        }
    }
    std::cout << i << " " << m_sources.size() << std::endl;
}

bool AttributeTranslator::Load(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        file.close();
        return false;
    }

    std::string line;
    while (std::getline(file, line))
    {
        if (line.empty())
        {
            continue;
        }

        std::string att, val;
        std::stringstream str(line);

        std::getline(str, att, ',');
        std::getline(str, val, ',');
        std::string source_str = att + "," + val;
        AttValPair source(att, val);

        std::getline(str, att, ',');
        std::getline(str, val, ',');
        AttValPair compatible(att, val);

        std::vector<AttValPair> **existing_avps = m_translator.search(source_str);
        if (existing_avps == nullptr)
        {
            std::vector<AttValPair> *new_avps = new std::vector<AttValPair>({compatible});
            m_translator.insert(source_str, new_avps);
            m_sources.insert(source_str);
        }
        else
        {
            (*existing_avps)->push_back(compatible);
        }
    }
    file.close();
    return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(
    const AttValPair &source) const
{
    // O(N)
    // N: number of source attribute-value pairs
    std::vector<AttValPair> **avps = m_translator.search(source.attribute + "," + source.value);
    if (avps == nullptr)
    {
        return std::vector<AttValPair>();
    }
    return **avps;
}
