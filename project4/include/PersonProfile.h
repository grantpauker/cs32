#ifndef PERSON_PROFILE_H
#define PERSON_PROFILE_H
#include "RadixTree.h"
#include "provided.h"
#include <string>
#include <unordered_set>

class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email) : m_name(name), m_email(email), m_pair_count(0){};
    ~PersonProfile(){};

    std::string GetName() const { return m_name; }
    std::string GetEmail() const { return m_email; }

    void AddAttValPair(const AttValPair &attval);
    int GetNumAttValPairs() const { return m_pair_count; }

    bool GetAttVal(int attribute_num, AttValPair &attval) const;

private:
    std::string m_name;
    std::string m_email;
    RadixTree<std::unordered_set<std::string>> m_att_val; // attribute -> unordered set of values
    std::unordered_set<std::string> m_attributes; // all associated attributes
    int m_pair_count;
};
#endif
