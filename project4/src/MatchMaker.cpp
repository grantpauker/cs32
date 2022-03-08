#include "MatchMaker.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "provided.h"
#include "utility.h"
#include <map>
#include <unordered_set>
#include <vector>

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
    // get profile from email
    PersonProfile profile = *m_database.GetMemberByEmail(email);

    // get set of compatible pairs for profile
    std::unordered_set<AttValPair> compatible_pairs;
    for (int i = 0; i < profile.GetNumAttValPairs(); i++)
    {
        AttValPair source;
        profile.GetAttVal(i, source);
        std::vector<AttValPair> current_compatible = m_translator.FindCompatibleAttValPairs(source);
        std::copy(current_compatible.begin(), current_compatible.end(), std::inserter(compatible_pairs, compatible_pairs.end()));
    }

    // create map from email address to number of compatible pairs they have
    std::unordered_map<std::string, int> emails;
    for (AttValPair compatible : compatible_pairs)
    {
        for (auto match_email : m_database.FindMatchingMembers(compatible))
        {
            if (match_email == email)
            {
                continue;
            }
            if (emails.find(match_email) == emails.end())
            {
                emails[match_email] = 1;
            }
            else
            {
                emails[match_email]++;
            }
        }
    }

    // create list of emails over threshold
    std::vector<EmailCount> email_counts;
    for (auto pair : emails)
    {
        if (pair.second >= threshold)
        {
            email_counts.push_back(EmailCount(pair.first, pair.second));
        }
    }
    std::sort(email_counts.begin(), email_counts.end(), compareEmailCounts);
    return email_counts;
}
