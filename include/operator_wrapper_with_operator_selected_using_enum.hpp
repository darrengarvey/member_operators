
#ifndef OPERATOR_WRAPPER_WITH_OPERATOR_SELECTED_USING_ENUM_INCLUDED
#define OPERATOR_WRAPPER_WITH_OPERATOR_SELECTED_USING_ENUM_INCLUDED

namespace ops {

enum OpType
{
    LessThan,
    GreaterThan,
    EqualTo
};

template<typename Struct, typename T>
struct OperatorWrapper
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr, const enum OpType _op)
        : member(member_ptr)
        , op(_op)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
#if defined(TYPE11)
        return op == LessThan ? s1.*member < s2.*member
             : op == GreaterThan ? s1.*member > s2.*member
             : s1.*member == s2.*member;
#elif defined(TYPE12)
        bool result;
        switch(op)
        {
        case LessThan: result = s1.*member < s2.*member; break;
        case GreaterThan: result = s1.*member > s2.*member; break;
        case EqualTo: result = s1.*member == s2.*member; break;
        default: break;
        }
        return result;
#elif defined(TYPE13)
        switch(op)
        {
        case LessThan: return s1.*member < s2.*member;
        case GreaterThan: return s1.*member > s2.*member;
        case EqualTo: return s1.*member == s2.*member;
        default: return false;
        }
#endif
    }

    const member_ptr member;
    const enum OpType op;
};

template< typename T, typename Struct >
OperatorWrapper<Struct, T>
inline less_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T>(member_ptr, LessThan);
}

template< typename T, typename Struct >
OperatorWrapper<Struct, T>
inline greater_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T>(member_ptr, GreaterThan);
}

template< typename T, typename Struct >
OperatorWrapper<Struct, T>
inline equal_to(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T>(member_ptr, EqualTo);
}

} /* ops */

#include "sort_functions_taking_member_pointer.hpp"

#endif /* OPERATOR_WRAPPER_WITH_OPERATOR_SELECTED_USING_ENUM_INCLUDED */

