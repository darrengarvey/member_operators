
#ifndef OPERATOR_WRAPPER_WITH_OPERATOR_PASSED_TO_IT_INCLUDED
#define OPERATOR_WRAPPER_WITH_OPERATOR_PASSED_TO_IT_INCLUDED

namespace ops {

template< typename T >
inline bool do_less_than(const T& t1, const T& t2)
{
    return t1 < t2;
}

template< typename T >
inline bool do_greater_than(const T& t1, const T& t2)
{
    return t1 > t2;
}

template< typename T >
inline bool do_equal_to(const T& t1, const T& t2)
{
    return t1 == t2;
}

template<typename Struct, typename T>
struct OperatorWrapper
{
    typedef T (Struct::* const member_ptr);
    typedef bool (*operator_type)(const T&, const T&);

    OperatorWrapper(T Struct::* const member_ptr, operator_type _op)
        : member(member_ptr)
        , op(_op)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        return op(s1.*member, s2.*member);
    }

    const member_ptr member;
    const operator_type op;
};

template< typename T, typename Struct >
OperatorWrapper<Struct, T>
inline less_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T>(member_ptr, &do_less_than<T>);
}

template< typename T, typename Struct >
OperatorWrapper<Struct, T>
inline greater_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T>(member_ptr, &do_greater_than<T>);
}

template< typename T, typename Struct >
OperatorWrapper<Struct, T>
inline equal_to(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T>(member_ptr, &do_equal_to<T>);
}

} /* ops */

#include "sort_functions_taking_member_pointer.hpp"

#endif /* OPERATOR_WRAPPER_WITH_OPERATOR_PASSED_TO_IT_INCLUDED */

