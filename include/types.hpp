
#ifndef TYPES_HPP
#define TYPES_HPP

#include <string>

struct Type
{
    Type(std::string _s, int _num)
        : s(_s), num(_num)
    {}

    std::string s;
    int num;
};

#endif // TYPES_HPP

