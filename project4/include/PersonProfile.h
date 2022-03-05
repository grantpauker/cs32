#ifndef PERSON_PROFILE_H
#define PERSON_PROFILE_H
#include "provided.h"
#include <string>
#include <vector>
class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email) : m_name(name), m_email(email){};
    ~PersonProfile(){};
    std::string GetName() const { return m_name; }
    std::string GetEmail() const { return m_email; }
    void AddAttValPair(const AttValPair &attval)
    {
        m_attval_pairs.push_back(attval);
    }
    int GetNumAttValPairs() const
    {
        return m_attval_pairs.size();
    }
    bool GetAttVal(int attribute_num, AttValPair &attval) const // <O(N)
    {
        if (0 > attribute_num || attribute_num >= GetNumAttValPairs())
        {
            return false;
        }
        attval = m_attval_pairs[attribute_num];
        return true;
    }

    void print() const
    {
        std::cout << m_name << '\n'
                  << m_email << '\n'
                  << GetNumAttValPairs() << '\n';
        for (auto avp : m_attval_pairs)
        {
            std::cout << avp << '\n';
        }
        std::cout << std::flush;
    }

private:
    std::string m_name;
    std::string m_email;
    std::vector<AttValPair> m_attval_pairs; // TODO is vector good?
};
#endif
