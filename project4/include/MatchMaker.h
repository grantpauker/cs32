#ifndef MATCHMAKER_H
#define MATCHMAKER_H
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "provided.h"
#include <unordered_set>
#include <vector>
class MatchMaker
{
public:
    MatchMaker(const MemberDatabase &mdb, const AttributeTranslator &at) : m_database(mdb), m_translator(at) {}
    ~MatchMaker() {}

    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const
    {
        PersonProfile profile = *m_database.GetMemberByEmail(email);
        std::list<AttValPair> compatible_pairs; // TODO handle duplicates
        for (int i = 0; i < profile.GetNumAttValPairs(); i++)
        {
            AttValPair compatible;
            profile.GetAttVal(i, compatible);
            compatible_pairs.push_back(compatible);
        }
        std::vector<EmailCount> compatible_emails;
        for (AttValPair compatible : compatible_pairs)
        {
            addEmails(&compatible_emails, compatible);
        }
        return compatible_emails;
    }

private:
    MemberDatabase m_database;
    AttributeTranslator m_translator;
    void addEmails(std::vector<EmailCount> *email_counts, AttValPair avp) const {

    }
};
#endif
