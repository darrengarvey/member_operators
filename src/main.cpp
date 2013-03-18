
#include <iostream>
#include <string>
#include <vector>
#include <typeinfo>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/assign/list_of.hpp>

using namespace std;
using namespace boost::assign;

struct Type
{
    Type(string _s, int _num) : s(_s), num(_num) {}

    string s;
    int num;
};

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
#elif defined(TYPE2)
bool less_than(const Type& t1, const Type& t2)
{
    return t1.s < t2.s;
}
#elif defined(TYPE3)
struct LessThan
{
    bool operator()(const Type& t1, const Type& t2)
    {
        return t1.s < t2.s;
    }
};
#elif defined(TYPE4)
template< typename Struct >
struct LessThan
{
    bool operator()(const Struct& t1, const Struct& t2)
    {
        return t1.s < t2.s;
    }
};
#elif defined(TYPE5)
template<typename Struct, typename T>
struct OperatorWrapper
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

template< typename T, typename Struct >
OperatorWrapper<Struct, T>
less_than(T Struct::*member_ptr)
{
    return OperatorWrapper<Struct, T>(member_ptr);
}
#elif defined(TYPE6)
boost::function< bool(const Type&, const Type&) >
less_than()
{
    return boost::bind(&Type::s, _1) < boost::bind(&Type::s, _2);
}
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
#endif

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

int main(int, char**)
{
    vector< Type > types = list_of
        ( Type("one", 1) )
        ( Type("two", 2 ) )
        ( Type("three", 3 ) )
        ( Type("f    our", 4 ) );

#if defined(TYPE1)
    sort( types.begin(), types.end(), less_than(&Type::s) );
    //less_than(&Type::s);
#elif defined(TYPE2)
    sort( types.begin(), types.end(), &less_than );
    //&less_than;
#elif defined(TYPE3)
    sort( types.begin(), types.end(), LessThan() );
    //LessThan();
#elif defined(TYPE4)
    sort( types.begin(), types.end(), LessThan<Type>() );
    //LessThan<Type>();
#elif defined(TYPE5)
    sort( types.begin(), types.end(), less_than(&Type::s) );
    //less_than(&Type::s);
#elif defined(TYPE6)
    sort( types.begin(), types.end(), less_than() );
    //less_than();
#elif defined(TYPE7)
    sort( types.begin(), types.end(), less_than<string, Type, &Type::s>() );
    //less_than<string, Type, &Type::s>();
#elif defined(TYPE8)
    sort( types.begin(), types.end(), less_than(&Type::s) );
    //less_than(&Type::s);
#endif

    print( types, &Type::s );

    return 0;
}
