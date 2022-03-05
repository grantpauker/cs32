#ifndef PROVIDED_H
#define PROVIDED_H

#include <iostream>
#include <string>

struct AttValPair
{
    AttValPair(std::string att, std::string val)
        : attribute(att), value(val)
    {
    }

    AttValPair()
    {
    }

    std::string attribute;
    std::string value;

    bool operator==(const AttValPair &rhs) const
    {
        return (attribute == rhs.attribute && value == rhs.value);
    }

    bool operator!=(const AttValPair &rhs) const
    {
        return !(*this == rhs);
    }

#ifndef FINAL
    friend std::ostream &operator<<(std::ostream &out, const AttValPair &avp);
#endif
};
#ifndef FINAL
std::ostream &operator<<(std::ostream &out, const AttValPair &avp)
{
    out << "(" << avp.attribute << ", " << avp.value << ")";
    return out;
}
#endif

struct EmailCount
{
    EmailCount(std::string em, int ct)
        : email(em), count(ct)
    {
    }

    std::string email;
    int count;
};

#endif // PROVIDED_H