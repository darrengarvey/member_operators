
#ifndef HARD_CODED_FUNCTIONS_INCLUDED
#define HARD_CODED_FUNCTIONS_INCLUDED

#include "types.hpp"

#if defined(TYPE1)
#  define INLINE
#elif defined(TYPE2)
#  define INLINE inline
#endif

namespace ops {

INLINE bool less_than(const Type& t1, const Type& t2)
{
    return t1.s < t2.s;
}

INLINE bool greater_than(const Type& t1, const Type& t2)
{
    return t1.s > t2.s;
}

INLINE bool equal_to(const Type& t1, const Type& t2)
{
    return t1.s == t2.s;
}

} /* ops */

template< typename T >
void sort_less_than(T& types)
{
    std::sort( types.begin(), types.end(), ops::less_than );
}

template< typename T >
void sort_greater_than(T& types)
{
    std::sort( types.begin(), types.end(), ops::greater_than );
}

template< typename T >
void sort_equal_to(T& types)
{
    std::sort( types.begin(), types.end(), ops::equal_to );
}

#endif /* HARD_CODED_FUNCTIONS_INCLUDED */

