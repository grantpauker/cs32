#include "PersonProfile.h"
#include "provided.h"
#include <string>
#include <unordered_set>
#include <vector>

void PersonProfile::AddAttValPair(const AttValPair &attval)
{
    // O(N)
    // N: number of attribute-value pairs stored
    m_attributes.insert(attval.attribute);
    std::unordered_set<std::string> *found_values = m_att_val.search(attval.attribute);
    if (found_values != nullptr)
    {
        if (!found_values->insert(attval.value).second)
        {
            return;
        }
    }
    else
    {
        std::unordered_set<std::string> *new_values = new std::unordered_set<std::string>();
        new_values->insert(attval.value);
        m_att_val.insert(attval.attribute, *new_values);
    }
    m_pair_count++;
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair &attval) const
{
    // O(N)
    // N: number of attribute-value pairs stored
    if (0 > attribute_num || attribute_num >= GetNumAttValPairs())
    {
        return false;
    }
    int i = 0;
    for (auto attribute : m_attributes)
    {
        std::unordered_set<std::string> values = *m_att_val.search(attribute);
        for (auto value : values)
        {
            if (i == attribute_num)
            {
                attval = AttValPair(attribute, value);
                return true;
            }
            i++;
        }
    }
    return false;
}
