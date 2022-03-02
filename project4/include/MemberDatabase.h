#ifndef MEMBER_DATABASE_H
#define MEMBER_DATABASE_H
#include "PersonProfile.h"
#include "provided.h"
#include <vector>

class MemberDatabase
{
public:
    MemberDatabase() {}
    ~MemberDatabase() {}
    bool LoadDatabase(std::string filename) { return false; };

    std::vector<std::string> FindMatchingMembers(const AttValPair &input) const
    {
        std::vector<std::string> v;
        return v;
    }

    const PersonProfile *GetMemberByEmail(std::string email) const
    {
        PersonProfile *p = nullptr;
        return p;
    }
};
#endif
