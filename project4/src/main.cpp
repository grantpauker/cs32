#include "AttributeTranslator.h"
#include "MatchMaker.h"
#include "MemberDatabase.h"
#include "PersonProfile.h"
#include "provided.h"
#include <string>
#include <vector>
const std::string MEMBERS_FILE = "data/members.txt";
const std::string TRANSLATOR_FILE = "data/translator.txt";

bool findMatches(const MemberDatabase &mdb, const AttributeTranslator &at);

int main()
{
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
    {
    }
    

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase &mdb, const AttributeTranslator &at)
{
    // Prompt for email
    std::string email;
    const PersonProfile *pp;
    for (;;)
    {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        email = "AbFow2483@charter.net";
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

    // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++)
    {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }
    AttributeTranslator translator;
    std::vector<AttValPair> v = translator.FindCompatibleAttValPairs(AttValPair("job", "architect"));

    for(auto avp : v){
        std::cout << avp << std::endl;
    }
    /*

    // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

    // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else
    {
        std::cout << "The following members were good matches:" << std::endl;
        ;
        for (const auto &emailCount : emails)
        {
            const PersonProfile *pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                      << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    */
    return false;
}
