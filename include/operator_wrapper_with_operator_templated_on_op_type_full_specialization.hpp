
#ifndef OPERATOR_WRAPPER_WITH_OPERATOR_TEMPLATED_ON_OP_TYPE_ENABLE_IF_INCLUDED
#define OPERATOR_WRAPPER_WITH_OPERATOR_TEMPLATED_ON_OP_TYPE_ENABLE_IF_INCLUDED

namespace ops {

struct LessThanOp {};
struct GreaterThanOp {};
struct EqualToOp {};

template<typename Struct, typename T, typename Op>
struct OperatorWrapper
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr)
        : member(member_ptr)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const;

    const member_ptr member;
};

template<typename Struct, typename T>
struct OperatorWrapper<Struct, T, LessThanOp>
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr)
        : member(member_ptr)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        return s1.*member < s2.*member;
    }

    const member_ptr member;
};

template<typename Struct, typename T>
struct OperatorWrapper<Struct, T, GreaterThanOp>
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr)
        : member(member_ptr)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        return s1.*member > s2.*member;
    }

    const member_ptr member;
};

template<typename Struct, typename T>
struct OperatorWrapper<Struct, T, EqualToOp>
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr)
        : member(member_ptr)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        return s1.*member == s2.*member;
    }

    const member_ptr member;
};

template< typename T, typename Struct >
OperatorWrapper<Struct, T, LessThanOp>
inline less_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T, LessThanOp>(member_ptr);
}

template< typename T, typename Struct >
OperatorWrapper<Struct, T, GreaterThanOp>
inline greater_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T, GreaterThanOp>(member_ptr);
}

template< typename T, typename Struct >
OperatorWrapper<Struct, T, EqualToOp>
inline equal_to(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T, EqualToOp>(member_ptr);
}

} /* ops */

#include "sort_functions_taking_member_pointer.hpp"

#endif /* OPERATOR_WRAPPER_WITH_OPERATOR_TEMPLATED_ON_OP_TYPE_ENABLE_IF_INCLUDED */

