
#ifndef SORT_FUNCTIONS_TAKING_MEMBER_POINTER_INCLUDED
#define SORT_FUNCTIONS_TAKING_MEMBER_POINTER_INCLUDED

template< typename T >
void sort_less_than(T& types)
{
    typedef typename T::value_type V;
    std::sort( types.begin(), types.end(), ops::less_than(&V::s) );
}

template< typename T >
void sort_greater_than(T& types)
{
    typedef typename T::value_type V;
    std::sort( types.begin(), types.end(), ops::greater_than(&V::s) );
}

template< typename T >
void sort_equal_to(T& types)
{
    typedef typename T::value_type V;
    std::sort( types.begin(), types.end(), ops::equal_to(&V::s) );
}

#endif /* SORT_FUNCTIONS_TAKING_MEMBER_POINTER_INCLUDED */

