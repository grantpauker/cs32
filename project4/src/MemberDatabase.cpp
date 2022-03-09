#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "RadixTree.h"
#include "provided.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

MemberDatabase::~MemberDatabase()
{
    for (auto email : m_emails)
    {
        PersonProfile **profile = m_email_to_profile.search(email);
        if (profile != nullptr)
        {
            if (*profile != nullptr)
            {
                delete *profile;
            }
        }
    }
}

bool MemberDatabase::LoadDatabase(std::string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        file.close();
        return false;
    }
    bool success = false;
    while (1)
    {
        std::string name, email, count_str, line;
        std::getline(file, name);
        std::getline(file, email);
        std::getline(file, count_str);
        int count = std::stoi(count_str);

        PersonProfile *profile = new PersonProfile(name, email);
        if (!m_emails.insert(email).second)
        {
            return false;
        }

        for (int i = 0; i < count; i++)
        {
            std::getline(file, line);
            std::stringstream str(line);

            std::string att, val;
            std::getline(str, att, ',');
            std::getline(str, val, ',');

            AttValPair avp(att, val);
            profile->AddAttValPair(avp);

            std::vector<std::string> **existing_emails = m_avp_to_emails.search(line);
            if (existing_emails == nullptr)
            {
                std::vector<std::string> *new_emails = new std::vector<std::string>({email});
                m_avp_to_emails.insert(line, new_emails);
            }
            else
            {
                (*existing_emails)->push_back(email);
            }
        }
        m_email_to_profile.insert(email, profile);

        if (!std::getline(file, line))
        {
            success = true;
            break;
        }
    }
    file.close();
    return success;
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair &input) const
{
    // O(P+M)
    // P: total number of distinct avp pairs in population
    // M: number of members that have the given pair
    std::vector<std::string> **matching_emails = m_avp_to_emails.search(input.attribute + "," + input.value);
    if (matching_emails == nullptr)
    {
        return std::vector<std::string>();
    }
    return **matching_emails;
}

const PersonProfile *MemberDatabase::GetMemberByEmail(std::string email) const
{
    // O(N)
    // N: total number of members
    PersonProfile **profile = m_email_to_profile.search(email);
    if (profile == nullptr)
    {
        return nullptr;
    }
    return *profile;
}
