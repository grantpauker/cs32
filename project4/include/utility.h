#ifndef UTILITY_H
#define UTILITY_H
#include "provided.h"
#include <string>

// hash an attvalpair as a string
template <>
struct std::hash<AttValPair>
{
    std::size_t operator()(const AttValPair &k) const
    {
        return std::hash<std::string>()(k.attribute + "," + k.value);
    }
};
#endif
