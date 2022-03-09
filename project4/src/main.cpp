#include "AttributeTranslator.h"
#include "MatchMaker.h"
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "provided.h"
#include <chrono>
#include <string>
#include <vector>

const std::string MEMBERS_FILE = "data/members.txt";
const std::string TRANSLATOR_FILE = "data/translator.txt";

bool findMatches(const MemberDatabase &mdb, const AttributeTranslator &at);

int main()
{
    auto t0 = std::chrono::high_resolution_clock::now();
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto mdb_time = std::chrono::duration_cast<std::chrono::milliseconds>(t1 - t0);
    auto at_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
    std::cout << "member database: " << mdb_time.count() << "ms" << std::endl;
    std::cout << "attribute translator: " << at_time.count() << "ms" << std::endl;

    while (findMatches(mdb, at))
    {
    }

    std::cout << "Happy dating!" << std::endl;
}
bool findMatches(const MemberDatabase &mdb, const AttributeTranslator &at)
{
    // prompt for email
    std::string email;
    const PersonProfile *pp;
    while (1)
    {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        email = "AbFow2483@charter.net";
        std::getline(std::cin, email);
        if (email.empty())
        {
            return false;
        }
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
        {
            break;
        }
        std::cout << "That email is not in the member database." << std::endl;
    }

    // show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++)
    {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }
    AttributeTranslator translator;
    std::vector<AttValPair> v = translator.FindCompatibleAttValPairs(AttValPair("job", "architect"));

    // prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

    // print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
    {
        std::cout << "No member was a good enough match." << std::endl;
    }
    else
    {
        std::cout << "The following members were good matches:" << std::endl;
        for (const auto &emailCount : emails)
        {
            const PersonProfile *pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}
