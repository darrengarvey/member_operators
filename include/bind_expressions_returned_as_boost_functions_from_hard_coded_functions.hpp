
#ifndef BIND_EXPRESSIONS_RETURNED_AS_BOOST_FUNCTIONS_FROM_HARD_CODED_FUNCTIONS_INCLUDED
#define BIND_EXPRESSIONS_RETURNED_AS_BOOST_FUNCTIONS_FROM_HARD_CODED_FUNCTIONS_INCLUDED

#include "types.hpp"

namespace ops {

boost::function< bool(const Type&, const Type&) >
less_than()
{
    return boost::bind(&Type::s, _1) < boost::bind(&Type::s, _2);
}

boost::function< bool(const Type&, const Type&) >
greater_than()
{
    return boost::bind(&Type::s, _1) > boost::bind(&Type::s, _2);
}

boost::function< bool(const Type&, const Type&) >
equal_to()
{
    return boost::bind(&Type::s, _1) == boost::bind(&Type::s, _2);
}

} /* ops */

template< typename T >
void sort_less_than(T& types)
{
    std::sort( types.begin(), types.end(), ops::less_than() );
}

template< typename T >
void sort_greater_than(T& types)
{
    std::sort( types.begin(), types.end(), ops::greater_than() );
}

template< typename T >
void sort_equal_to(T& types)
{
    std::sort( types.begin(), types.end(), ops::equal_to() );
}


#endif /* BIND_EXPRESSIONS_RETURNED_AS_BOOST_FUNCTIONS_FROM_HARD_CODED_FUNCTIONS_INCLUDED */

