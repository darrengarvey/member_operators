
#ifndef BIND_EXPRESSIONS_INLINE_INCLUDED
#define BIND_EXPRESSIONS_INLINE_INCLUDED

template< typename T >
void sort_less_than(T& types)
{
    typedef typename T::value_type V;
    std::sort( types.begin(), types.end(), boost::bind(&V::s, _1) < boost::bind(&V::s, _2) );
}

template< typename T >
void sort_greater_than(T& types)
{
    typedef typename T::value_type V;
    std::sort( types.begin(), types.end(), boost::bind(&V::s, _1) > boost::bind(&V::s, _2) );
}

template< typename T >
void sort_equal_to(T& types)
{
    typedef typename T::value_type V;
    std::sort( types.begin(), types.end(), boost::bind(&V::s, _1) == boost::bind(&V::s, _2) );
}

#endif /* BIND_EXPRESSIONS_INLINE_INCLUDED */

