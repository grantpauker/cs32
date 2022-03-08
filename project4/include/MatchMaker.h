#ifndef MATCH_MAKER_H
#define MATCH_MAKER_H
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "provided.h"
#include <string>

class MatchMaker
{
public:
    MatchMaker(const MemberDatabase &mdb, const AttributeTranslator &at) : m_database(mdb), m_translator(at) {}
    ~MatchMaker() {}

    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;

private:
    const MemberDatabase &m_database;
    const AttributeTranslator &m_translator;

    static bool compareEmailCounts(EmailCount a, EmailCount b) { return (a.count > b.count) || (a.count == b.count && a.email < b.email); }
};
#endif
