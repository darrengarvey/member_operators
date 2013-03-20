
#ifndef HARD_CODED_FUNCTION_OBJECT_INCLUDED
#define HARD_CODED_FUNCTION_OBJECT_INCLUDED

#include "types.hpp"

namespace ops {

struct LessThan
{
    bool operator()(const Type& t1, const Type& t2) const
    {
        return t1.s < t2.s;
    }
};

struct GreaterThan
{
    bool operator()(const Type& t1, const Type& t2) const
    {
        return t1.s > t2.s;
    }
};

struct EqualTo
{
    bool operator()(const Type& t1, const Type& t2) const
    {
        return t1.s == t2.s;
    }
};

} /* ops */

template< typename T >
void sort_less_than(T& types)
{
    std::sort( types.begin(), types.end(), ops::LessThan() );
}

template< typename T >
void sort_greater_than(T& types)
{
    std::sort( types.begin(), types.end(), ops::GreaterThan() );
}

template< typename T >
void sort_equal_to(T& types)
{
    std::sort( types.begin(), types.end(), ops::EqualTo() );
}

#endif /* HARD_CODED_FUNCTION_OBJECT_INCLUDED */

