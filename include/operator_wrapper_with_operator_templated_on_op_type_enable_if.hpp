
#ifndef OPERATOR_WRAPPER_WITH_OPERATOR_TEMPLATED_ON_OP_TYPE_ENABLE_IF_INCLUDED
#define OPERATOR_WRAPPER_WITH_OPERATOR_TEMPLATED_ON_OP_TYPE_ENABLE_IF_INCLUDED

namespace ops {

enum OpType
{
    LessThan,
    GreaterThan,
    EqualTo
};

template< int Comparison > 
struct enum_is_same : boost::false_type {};

template<> 
struct enum_is_same<0> : boost::true_type {};

template<typename Struct, typename T, int OpType>
struct OperatorWrapper
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr)
        : member(member_ptr)
    {
    }

    template< typename StructType >
    typename boost::enable_if<
        boost::mpl::and_<
            boost::is_same<StructType, Struct>,
            enum_is_same< OpType - LessThan >
        >, bool >::type
    operator()(const StructType& s1, const StructType& s2) const
    {
        return s1.*member < s2.*member;
    }

    template< typename StructType >
    //typename boost::enable_if_c< OpType == GreaterThan, bool >::type
    typename boost::enable_if<
        boost::mpl::and_<
            boost::is_same<StructType, Struct>,
            enum_is_same< OpType - GreaterThan >
        >, bool >::type
    operator()(const StructType& s1, const StructType& s2) const
    {
        return s1.*member > s2.*member;
    }

    template< typename StructType >
    //typename boost::enable_if_c< OpType == EqualTo, bool >::type
    typename boost::enable_if<
        boost::mpl::and_<
            boost::is_same<StructType, Struct>,
            enum_is_same< OpType - EqualTo >
        >, bool >::type
    operator()(const StructType& s1, const StructType& s2) const
    {
        return s1.*member == s2.*member;
    }

    const member_ptr member;
};

template< typename T, typename Struct >
OperatorWrapper<Struct, T, LessThan>
inline less_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T, LessThan>(member_ptr);
}

template< typename T, typename Struct >
OperatorWrapper<Struct, T, GreaterThan>
inline greater_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T, GreaterThan>(member_ptr);
}

template< typename T, typename Struct >
OperatorWrapper<Struct, T, EqualTo>
inline equal_to(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T, EqualTo>(member_ptr);
}

} /* ops */

#include "sort_functions_taking_member_pointer.hpp"

#endif /* OPERATOR_WRAPPER_WITH_OPERATOR_TEMPLATED_ON_OP_TYPE_ENABLE_IF_INCLUDED */

