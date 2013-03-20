
#ifndef BIND_EXPRESSIONS_RETURNED_AS_BOOST_FUNCTIONS_INCLUDED
#define BIND_EXPRESSIONS_RETURNED_AS_BOOST_FUNCTIONS_INCLUDED

#include "types.hpp"

namespace ops {

boost::function< bool(const Type&, const Type&) >
less_than(std::string Type::*member)
{
    return boost::bind(member, _1) < boost::bind(member, _2);
}

boost::function< bool(const Type&, const Type&) >
greater_than(std::string Type::*member)
{
    return boost::bind(member, _1) > boost::bind(member, _2);
}

boost::function< bool(const Type&, const Type&) >
equal_to(std::string Type::*member)
{
    return boost::bind(member, _1) == boost::bind(member, _2);
}

} /* ops */

#include "sort_functions_taking_member_pointer.hpp"

#endif /* BIND_EXPRESSIONS_RETURNED_AS_BOOST_FUNCTIONS_INCLUDED */

