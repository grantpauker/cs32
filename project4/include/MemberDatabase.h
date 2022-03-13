#ifndef MEMBER_DATABASE_H
#define MEMBER_DATABASE_H
#include "PersonProfile.h"
#include "RadixTree.h"
#include "provided.h"
#include <list>
#include <set>
#include <string>
#include <vector>

class MemberDatabase
{
public:
    MemberDatabase() {}
    ~MemberDatabase();

    bool LoadDatabase(std::string filename);
    std::vector<std::string> FindMatchingMembers(const AttValPair &input) const;
    const PersonProfile *GetMemberByEmail(std::string email) const;

private:
    RadixTree<std::vector<std::string>*> m_avp_to_emails; // avp -> vector of email addresses
    RadixTree<PersonProfile *> m_email_to_profile;       // email address -> profile
    std::set<std::string> m_emails; // all loaded emails
    std::set<std::string> m_avps; // all loaded avps
};
#endif
