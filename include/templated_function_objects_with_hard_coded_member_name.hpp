
#ifndef TEMPLATED_FUNCTION_OBJECTS_WITH_HARD_CODED_MEMBER_NAME_INCLUDED
#define TEMPLATED_FUNCTION_OBJECTS_WITH_HARD_CODED_MEMBER_NAME_INCLUDED

namespace ops {

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

} /* ops */

template< typename T >
void sort_less_than(T& types)
{
    std::sort( types.begin(), types.end(), ops::LessThan<typename T::value_type>() );
}

template< typename T >
void sort_greater_than(T& types)
{
    std::sort( types.begin(), types.end(), ops::GreaterThan<typename T::value_type>() );
}

template< typename T >
void sort_equal_to(T& types)
{
    std::sort( types.begin(), types.end(), ops::EqualTo<typename T::value_type>() );
}

#endif /* TEMPLATED_FUNCTION_OBJECTS_WITH_HARD_CODED_MEMBER_NAME_INCLUDED */

