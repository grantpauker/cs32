#ifndef MATCHMAKER_H
#define MATCHMAKER_H
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "provided.h"
#include <vector>
class MatchMaker
{
public:
    MatchMaker(const MemberDatabase &mdb, const AttributeTranslator &at) {}
    ~MatchMaker() {}

    std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const
    {
        std::vector<EmailCount> v;
        return v;
    }
};
#endif
