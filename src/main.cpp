
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/timer/timer.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/utility/enable_if.hpp>

#if defined(TYPE1) || defined(TYPE2)
#  include "hard_coded_functions.hpp"
#elif defined(TYPE3)
#  include "hard_coded_function_objects.hpp"
#elif defined(TYPE4)
#  include "templated_function_objects_with_hard_coded_member_name.hpp"
#elif defined(TYPE5)
#  include "bind_expressions_returned_as_boost_functions_from_hard_coded_functions.hpp"
#elif defined(TYPE6)
#  include "bind_expressions_returned_as_boost_functions.hpp"
#elif defined(TYPE7)
#  include "bind_expressions_inline.hpp"
#elif defined(TYPE8)
#  include "operator_wrapper_with_operator_passed_to_it.hpp"
#elif defined(TYPE9)
#  include "operator_wrapper_with_operator_templated_on_op_type_enable_if.hpp"
#elif defined(TYPE10)
#  include "operator_wrapper_with_operator_templated_on_op_type_full_specialization.hpp"
#elif defined(TYPE11) || defined(TYPE12) || defined(TYPE13)
#  include "operator_wrapper_with_operator_selected_using_enum.hpp"
#elif defined(TYPE14)
#  include "operator_wrapper_clever_lookup.hpp"
#endif

#include "types.hpp"

using namespace boost::assign;

//#elif defined(TYPE7)
//template<typename T, typename Struct, T Struct::*member_ptr>
//struct OperatorWrapper
//{
//    static T Struct::* const member;
//
//    bool operator()(const Struct& s1, const Struct& s2) const
//    {
//        return s1.*member < s2.*member;
//    }
//};
//
//template<typename T, typename Struct, T Struct::*member_ptr>
//T Struct::* const OperatorWrapper<T, Struct, member_ptr>::member = member_ptr;
//
//template< typename T, typename Struct, T Struct::*member_ptr >
//OperatorWrapper<T, Struct, member_ptr>
//less_than()
//{
//    return OperatorWrapper<T, Struct, member_ptr>();
//}
//#elif defined(TYPE8)
//template<typename T, typename Struct, T Struct::*member_ptr>
//struct OperatorWrapper
//{
//    static T Struct::* const member;
//
//    bool operator()(const Struct& s1, const Struct& s2) const
//    {
//        return s1.*member < s2.*member;
//    }
//};
//
//template<typename T, typename Struct, T Struct::*member_ptr>
//T Struct::* const OperatorWrapper<T, Struct, member_ptr>::member = member_ptr;
//
//template< typename T, typename Struct >
//OperatorWrapper<T, Struct, member_ptr>
//less_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<T, Struct, member_ptr>();
//}
//#elif defined(TYPE10)
//#define BIND_MEMBER_OP(mem, op) \
//    boost::bind(&mem, _1) op boost::bind(&mem, _2)
//#elif defined(TYPE11)
//namespace ops
//{
//struct LessThanOp {};
//struct GreaterThanOp {};
//struct EqualToOp {};
//
//template<typename Struct, typename T, typename Op>
//struct OperatorWrapper
//{
//    typedef T (Struct::* const member_ptr);
//
//    OperatorWrapper(T Struct::* const member_ptr)
//        : member(member_ptr)
//    {
//    }
//
//    bool operator()(const Struct& s1, const Struct& s2) const;
//
//    const member_ptr member;
//};
//
//template<typename Struct, typename T>
//struct OperatorWrapper<Struct, T, LessThanOp>
//{
//    typedef T (Struct::* const member_ptr);
//
//    OperatorWrapper(T Struct::* const member_ptr)
//        : member(member_ptr)
//    {
//    }
//
//    bool operator()(const Struct& s1, const Struct& s2) const
//    {
//        return s1.*member < s2.*member;
//    }
//
//    const member_ptr member;
//};
//
//template<typename Struct, typename T>
//struct OperatorWrapper<Struct, T, GreaterThanOp>
//{
//    typedef T (Struct::* const member_ptr);
//
//    OperatorWrapper(T Struct::* const member_ptr)
//        : member(member_ptr)
//    {
//    }
//
//    bool operator()(const Struct& s1, const Struct& s2) const
//    {
//        return s1.*member > s2.*member;
//    }
//
//    const member_ptr member;
//};
//
//template<typename Struct, typename T>
//struct OperatorWrapper<Struct, T, EqualToOp>
//{
//    typedef T (Struct::* const member_ptr);
//
//    OperatorWrapper(T Struct::* const member_ptr)
//        : member(member_ptr)
//    {
//    }
//
//    bool operator()(const Struct& s1, const Struct& s2) const
//    {
//        return s1.*member == s2.*member;
//    }
//
//    const member_ptr member;
//};
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, LessThanOp>
//inline less_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, LessThanOp>(member_ptr);
//}
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, GreaterThanOp>
//inline greater_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, GreaterThanOp>(member_ptr);
//}
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, EqualToOp>
//inline equal_to(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, EqualToOp>(member_ptr);
//}
//
//} // namespace ops
//#elif defined(TYPE12)
//namespace ops
//{
//enum OpType
//{
//    LessThan,
//    GreaterThan,
//    EqualTo
//};
//
//template<typename Struct, typename T, int OpType>
//struct OperatorWrapper
//{
//    typedef T (Struct::* const member_ptr);
//
//    OperatorWrapper(T Struct::* const member_ptr)
//        : member(member_ptr)
//    {
//    }
//
//    bool operator()(const Struct& s1, const Struct& s2) const
//    {
//        return OpType == LessThan ? s1.*member < s2.*member
//             : OpType == GreaterThan ? s1.*member > s2.*member
//             : s1.*member == s2.*member;
//        // The above is more efficient than the below (or a switch statement).
//        //if (OpType == LessThan)
//        //{
//        //    return s1.*member < s2.*member;
//        //}
//        //else if (OpType == GreaterThan)
//        //{
//        //    return s1.*member > s2.*member;
//        //}
//        //else if (OpType == EqualTo)
//        //{
//        //    return s1.*member == s2.*member;
//        //}
//        //else
//        //{
//        //    return false;
//        //}
//    }
//
//    const member_ptr member;
//};
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, LessThan>
//inline less_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, LessThan>(member_ptr);
//}
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, GreaterThan>
//inline greater_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, GreaterThan>(member_ptr);
//}
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, EqualTo>
//inline equal_to(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, EqualTo>(member_ptr);
//}
//
//} // namespace ops
////#elif defined(TYPE16)
////namespace ops
////{
////enum OpType
////{
////    LessThan,
////    GreaterThan,
////    EqualTo
////};
////
////template<typename Struct, typename T>
////struct OperatorWrapper
////{
////    typedef T (Struct::* const member_ptr);
////
////    OperatorWrapper(T Struct::* const member_ptr, enum OpType _op)
////        : member(member_ptr)
////        , op(_op)
////    {
////    }
////
////    bool operator()(const Struct& s1, const Struct& s2) const
////    {
////    }
////
////    const member_ptr member;
////    enum OpType op;
////};
////
////template< typename T, typename Struct >
////OperatorWrapper<Struct, T>
////inline less_than(T Struct::*member_ptr)
////{
////    return OperatorWrapper<Struct, T>(member_ptr, LessThan);
////}
////
////template< typename T, typename Struct >
////OperatorWrapper<Struct, T>
////inline greater_than(T Struct::*member_ptr)
////{
////    return OperatorWrapper<Struct, T>(member_ptr, GreaterThan);
////}
////
////template< typename T, typename Struct >
////OperatorWrapper<Struct, T>
////inline equal_to(T Struct::*member_ptr)
////{
////    return OperatorWrapper<Struct, T>(member_ptr, EqualTo);
////}
////
////} // namespace ops
//#elif defined(TYPE17) || defined(TYPE19) || defined(TYPE20)
//namespace ops
//{
//enum OpType
//{
//    LessThan,
//    GreaterThan,
//    EqualTo
//};
//struct LessThanOp { enum { value = LessThan }; };
//struct GreaterThanOp { enum { value = GreaterThan }; };
//struct EqualToOp { enum { value = EqualTo }; };
//
//template<typename Struct, typename T, typename Op>
//struct OperatorWrapper
//{
//    typedef T (Struct::* const member_ptr);
//
//    OperatorWrapper(T Struct::* const member_ptr)
//        : member(member_ptr)
//    {
//    }
//
//    bool operator()(const Struct& s1, const Struct& s2) const
//    {
//#if defined(TYPE17)
//        return static_cast<OpType>(Op::value) == LessThan ? s1.*member < s2.*member
//             : static_cast<OpType>(Op::value) == GreaterThan ? s1.*member > s2.*member
//             : s1.*member == s2.*member;
//#elif defined(TYPE19)
//        bool result;
//        switch (static_cast<OpType>(Op::value))
//        {
//        case LessThan: result = s1.*member < s2.*member; break;
//        case GreaterThan: result = s1.*member > s2.*member; break;
//        case EqualTo: result = s1.*member == s2.*member; break;
//        default: break;
//        }
//        return result;
//#elif defined(TYPE20)
//        switch(static_cast<OpType>(Op::value))
//        {
//        case LessThan: return s1.*member < s2.*member;
//        case GreaterThan: return s1.*member > s2.*member;
//        case EqualTo: return s1.*member == s2.*member;
//        default: return false;
//        }
//#endif
//    }
//
//    const member_ptr member;
//};
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, LessThanOp>
//inline less_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, LessThanOp>(member_ptr);
//}
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, GreaterThanOp>
//inline greater_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, GreaterThanOp>(member_ptr);
//}
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T, EqualToOp>
//inline equal_to(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T, EqualToOp>(member_ptr);
//}
//
//} // namespace ops
//#elif defined(TYPE21)
//#endif

using namespace std;

template< typename T, typename V > 
void print( vector<T>& stuff, V (T::* member_ptr) )
{
    for(size_t i=0; i < stuff.size(); ++i)
    {   
        if (i) cout<< ", ";
        cout<< stuff[i].*member_ptr;
    }   
    cout<< endl;
}

#ifndef MAX_ITERS
#  define MAX_ITERS 5000000
#endif

int main(int, char**)
{
    vector< Type > types = list_of
        ( Type("one", 1) )
        ( Type("two", 2 ) )
        ( Type("three", 3 ) )
        ( Type("four", 4 ) )
        ( Type("five", 5 ) )
        ( Type("six", 6 ) )
        ( Type("seven", 7 ) )
        ( Type("eight", 8 ) )
        ( Type("nine", 9 ) )
        ( Type("ten", 10 ) )
        ( Type("eleven", 11 ) )
        ( Type("twelve", 12 ) )
        ( Type("thirteen", 13 ) )
        ( Type("fourteen", 14 ) )
        ( Type("fifteen", 15 ) )
        ( Type("sixteen", 16 ) )
        ( Type("seventeen", 17 ) )
        ( Type("eighteen", 18 ) )
        ( Type("nineteen", 19 ) )
        ( Type("twenty", 20 ) );

    boost::timer::auto_cpu_timer timer;
    for( int i=0; i < MAX_ITERS; ++i )
    {
#if defined(LESS_THAN)
        sort_less_than( types );
#endif
#if defined(GREATER_THAN)
        sort_greater_than( types );
#endif
#if defined(EQUAL_TO)
        sort_equal_to( types );
#endif
//#elif defined(TYPE7)
//        sort( types.begin(), types.end(), less_than<string, Type, &Type::s>() );
//        //less_than<string, Type, &Type::s>();
    }

    print( types, &Type::s );

    return 0;
}
