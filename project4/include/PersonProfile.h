#ifndef PERSON_PROFILE_H
#define PERSON_PROFILE_H
#include "provided.h"
#include <string>
class PersonProfile
{
public:
    PersonProfile(std::string name, std::string email){};
    ~PersonProfile(){};
    std::string GetName() const { return ""; }
    std::string GetEmail() const { return ""; }
    void AddAttValPair(const AttValPair &attval)
    {
    }
    int GetNumAttValPairs() const
    {
        return 0;
    }
    bool GetAttVal(int attribute_num, AttValPair &attval) const
    {
        return false;
    }
};
#endif
