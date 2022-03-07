#ifndef MEMBER_DATABASE_H
#define MEMBER_DATABASE_H
#include "PersonProfile.h"
#include "RadixTree.h"
#include "provided.h"
#include <list>
#include <string>
#include <vector>

class MemberDatabase
{
public:
    MemberDatabase() {}
    ~MemberDatabase() {}
    bool LoadDatabase(std::string filename)
    {
        std::ifstream file;
        file.open(filename);
        for (int j = 0; j < 10000; j++) // TODO find end of file
        {
            std::string name, email, count_str;
            std::getline(file, name);
            std::getline(file, email);
            std::getline(file, count_str);
            int count = std::stoi(count_str);
            PersonProfile *profile = new PersonProfile(name, email);
            std::string line;
            for (int i = 0; i < count; i++)
            {
                std::getline(file, line);
                std::stringstream str(line);
                std::string att, val;
                std::getline(str, att, ',');
                std::getline(str, val, ',');
                AttValPair avp(att, val);
                profile->AddAttValPair(avp);
                if(email == "RomDeleon99@earthlink.net"){
                    int x= 0;
                }
                std::vector<std::string> **matching_emails = m_emails.search(line);
                if (matching_emails == nullptr)
                {
                    std::vector<std::string> *v = new std::vector<std::string>();
                    v->push_back(email);
                    m_emails.insert(line, v);
                }
                else
                {
                    if (*matching_emails == nullptr)
                    {
                        std::cout << email << std::endl;
                    }
                    else
                    {
                        (*matching_emails)->push_back(email);
                    }
                }
            }
            m_profiles.insert(email, profile);
            std::getline(file, line);
        }
        return true;
    }

    std::vector<std::string> FindMatchingMembers(const AttValPair &input) const
    {
        std::vector<std::string> **emails = m_emails.search(input.attribute + "," + input.value);
        if (emails == nullptr)
        {
            return std::vector<std::string>();
        }
        return **emails;
    }

    const PersonProfile *GetMemberByEmail(std::string email) const
    {
        return *m_profiles.search(email);
    }

private:
    RadixTree<std::vector<std::string> *> m_emails; // attribute-value pair -> email address
    RadixTree<PersonProfile *> m_profiles;          // email address -> profile
};
#endif
