
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
#endif

using namespace boost::assign;

#if defined(TYPE1)
template<typename Struct, typename T>
struct OperatorWrapper
{
    typedef T (Struct::*member_ptr);

    OperatorWrapper(T Struct::*member_ptr)
        : member(member_ptr)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        return s1.*member < s2.*member;
    }

    member_ptr member;
};

template< typename T, typename Struct >
boost::function< bool(const Struct&, const Struct&) >
less_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T>(member_ptr);
}
#elif defined(TYPE4)
template< typename Struct >
struct LessThan
{
    bool operator()(const Struct& t1, const Struct& t2) const
    {
        return t1.s < t2.s;
    }
};

template< typename Struct >
struct GreaterThan
{
    bool operator()(const Struct& t1, const Struct& t2) const
    {
        return t1.s > t2.s;
    }
};

template< typename Struct >
struct EqualTo
{
    bool operator()(const Struct& t1, const Struct& t2) const
    {
        return t1.s == t2.s;
    }
};
#elif defined(TYPE5)
namespace ops
{

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

} // namespace ops
#elif defined(TYPE6)
namespace ops
{

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

} // namespace ops
#elif defined(TYPE7)
template<typename T, typename Struct, T Struct::*member_ptr>
struct OperatorWrapper
{
    static T Struct::* const member;

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        return s1.*member < s2.*member;
    }
};

template<typename T, typename Struct, T Struct::*member_ptr>
T Struct::* const OperatorWrapper<T, Struct, member_ptr>::member = member_ptr;

template< typename T, typename Struct, T Struct::*member_ptr >
OperatorWrapper<T, Struct, member_ptr>
less_than()
{
    return OperatorWrapper<T, Struct, member_ptr>();
}
#elif defined(TYPE8)
template<typename T, typename Struct, T Struct::*member_ptr>
struct OperatorWrapper
{
    static T Struct::* const member;

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        return s1.*member < s2.*member;
    }
};

template<typename T, typename Struct, T Struct::*member_ptr>
T Struct::* const OperatorWrapper<T, Struct, member_ptr>::member = member_ptr;

template< typename T, typename Struct >
OperatorWrapper<T, Struct, member_ptr>
less_than(T Struct::*member_ptr)
{
    return OperatorWrapper<T, Struct, member_ptr>();
}
#elif defined(TYPE9)
// Nothing to see here. It's all inline below.
#elif defined(TYPE10)
#define BIND_MEMBER_OP(mem, op) \
    boost::bind(&mem, _1) op boost::bind(&mem, _2)
#elif defined(TYPE11)
namespace ops
{
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

} // namespace ops
#elif defined(TYPE12)
namespace ops
{
enum OpType
{
    LessThan,
    GreaterThan,
    EqualTo
};

template<typename Struct, typename T, int OpType>
struct OperatorWrapper
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr)
        : member(member_ptr)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        return OpType == LessThan ? s1.*member < s2.*member
             : OpType == GreaterThan ? s1.*member > s2.*member
             : s1.*member == s2.*member;
        // The above is more efficient than the below (or a switch statement).
        //if (OpType == LessThan)
        //{
        //    return s1.*member < s2.*member;
        //}
        //else if (OpType == GreaterThan)
        //{
        //    return s1.*member > s2.*member;
        //}
        //else if (OpType == EqualTo)
        //{
        //    return s1.*member == s2.*member;
        //}
        //else
        //{
        //    return false;
        //}
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

} // namespace ops
#elif defined(TYPE14)
namespace ops
{
enum OpType
{
    LessThan,
    GreaterThan,
    EqualTo
};
struct LessThanOp { enum { value = LessThan }; };
struct GreaterThanOp { enum { value = GreaterThan }; };
struct EqualToOp { enum { value = EqualTo }; };

template<typename Struct, typename T, typename Op>
struct OperatorWrapper
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr)
        : member(member_ptr)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
        switch (static_cast<OpType>(Op::value))
        {
        case LessThan:
            return s1.*member < s2.*member;
        case GreaterThan:
            return s1.*member > s2.*member;
        case EqualTo:
            return s1.*member == s2.*member;
        default:
            return false;
        }
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

} // namespace ops
#elif defined(TYPE15) || defined(TYPE16) || defined(TYPE18)
namespace ops
{
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
#if defined(TYPE15)
        return op == LessThan ? s1.*member < s2.*member
             : op == GreaterThan ? s1.*member > s2.*member
             : s1.*member == s2.*member;
#elif defined(TYPE16)
        bool result;
        switch(op)
        {
        case LessThan: result = s1.*member < s2.*member; break;
        case GreaterThan: result = s1.*member > s2.*member; break;
        case EqualTo: result = s1.*member == s2.*member; break;
        default: break;
        }
        return result;
#elif defined(TYPE18)
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

} // namespace ops
//#elif defined(TYPE16)
//namespace ops
//{
//enum OpType
//{
//    LessThan,
//    GreaterThan,
//    EqualTo
//};
//
//template<typename Struct, typename T>
//struct OperatorWrapper
//{
//    typedef T (Struct::* const member_ptr);
//
//    OperatorWrapper(T Struct::* const member_ptr, enum OpType _op)
//        : member(member_ptr)
//        , op(_op)
//    {
//    }
//
//    bool operator()(const Struct& s1, const Struct& s2) const
//    {
//    }
//
//    const member_ptr member;
//    enum OpType op;
//};
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T>
//inline less_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T>(member_ptr, LessThan);
//}
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T>
//inline greater_than(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T>(member_ptr, GreaterThan);
//}
//
//template< typename T, typename Struct >
//OperatorWrapper<Struct, T>
//inline equal_to(T Struct::*member_ptr)
//{
//    return OperatorWrapper<Struct, T>(member_ptr, EqualTo);
//}
//
//} // namespace ops
#elif defined(TYPE17) || defined(TYPE19) || defined(TYPE20)
namespace ops
{
enum OpType
{
    LessThan,
    GreaterThan,
    EqualTo
};
struct LessThanOp { enum { value = LessThan }; };
struct GreaterThanOp { enum { value = GreaterThan }; };
struct EqualToOp { enum { value = EqualTo }; };

template<typename Struct, typename T, typename Op>
struct OperatorWrapper
{
    typedef T (Struct::* const member_ptr);

    OperatorWrapper(T Struct::* const member_ptr)
        : member(member_ptr)
    {
    }

    bool operator()(const Struct& s1, const Struct& s2) const
    {
#if defined(TYPE17)
        return static_cast<OpType>(Op::value) == LessThan ? s1.*member < s2.*member
             : static_cast<OpType>(Op::value) == GreaterThan ? s1.*member > s2.*member
             : s1.*member == s2.*member;
#elif defined(TYPE19)
        bool result;
        switch (static_cast<OpType>(Op::value))
        {
        case LessThan: result = s1.*member < s2.*member; break;
        case GreaterThan: result = s1.*member > s2.*member; break;
        case EqualTo: result = s1.*member == s2.*member; break;
        default: break;
        }
        return result;
#elif defined(TYPE20)
        switch(static_cast<OpType>(Op::value))
        {
        case LessThan: return s1.*member < s2.*member;
        case GreaterThan: return s1.*member > s2.*member;
        case EqualTo: return s1.*member == s2.*member;
        default: return false;
        }
#endif
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

} // namespace ops
#elif defined(TYPE21)
namespace ops
{
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

} // namespace ops
#endif

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
#  define MAX_ITERS 1000000
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
#if defined(TYPE1)
        //less_than(&Type::s);
#elif defined(TYPE2)
        sort( types.begin(), types.end(), &ops::less_than );
        sort( types.begin(), types.end(), &ops::greater_than );
        sort( types.begin(), types.end(), &ops::equal_to );
        //&less_than;
#elif defined(TYPE3)
        sort( types.begin(), types.end(), LessThan() );
        sort( types.begin(), types.end(), GreaterThan() );
        sort( types.begin(), types.end(), EqualTo() );
        //LessThan();
#elif defined(TYPE4)
        sort( types.begin(), types.end(), LessThan<Type>() );
        sort( types.begin(), types.end(), GreaterThan<Type>() );
        sort( types.begin(), types.end(), EqualTo<Type>() );
        //LessThan<Type>();
#elif defined(TYPE6)
        sort( types.begin(), types.end(), ops::less_than() );
        sort( types.begin(), types.end(), ops::greater_than() );
        sort( types.begin(), types.end(), ops::equal_to() );
        //less_than();
#elif defined(TYPE7)
        sort( types.begin(), types.end(), less_than<string, Type, &Type::s>() );
        //less_than<string, Type, &Type::s>();
#elif defined(TYPE8)
        sort( types.begin(), types.end(), less_than(&Type::s) );
        //less_than(&Type::s);
#elif defined(TYPE9)
        sort( types.begin(), types.end(), boost::bind(&Type::s, _1) < boost::bind(&Type::s, _2) );
        sort( types.begin(), types.end(), boost::bind(&Type::s, _1) > boost::bind(&Type::s, _2) );
        sort( types.begin(), types.end(), boost::bind(&Type::s, _1) == boost::bind(&Type::s, _2) );
#elif defined(TYPE10)
        sort( types.begin(), types.end(), BIND_MEMBER_OP(Type::s, <) );
        sort( types.begin(), types.end(), BIND_MEMBER_OP(Type::s, >) );
        sort( types.begin(), types.end(), BIND_MEMBER_OP(Type::s, ==) );
#elif defined(TYPE5) \
   || defined(TYPE11) \
   || defined(TYPE12) \
   || defined(TYPE14) \
   || defined(TYPE15) \
   || defined(TYPE16) \
   || defined(TYPE17) \
   || defined(TYPE18) \
   || defined(TYPE19) \
   || defined(TYPE20) \
   || defined(TYPE21)
        sort( types.begin(), types.end(), ops::less_than(&Type::s) );
        sort( types.begin(), types.end(), ops::greater_than(&Type::s) );
        sort( types.begin(), types.end(), ops::equal_to(&Type::s) );
#endif
    }

    print( types, &Type::s );

    return 0;
}
