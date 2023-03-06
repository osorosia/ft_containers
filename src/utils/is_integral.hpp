#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

namespace ft {

// https://en.cppreference.com/w/cpp/types/integral_constant
template < class T, T v >
struct integral_constant {
    static const T            value = v;
    typedef T                 value_type;
    typedef integral_constant type;

    operator value_type() const { return value; }

    value_type operator()() const { return value; }
};

typedef integral_constant< bool, true >  true_type;
typedef integral_constant< bool, false > false_type;
template < bool B >
struct bool_constant : integral_constant< bool, B > {};

// https://en.cppreference.com/w/cpp/types/is_integral
template < class T >
struct is_integral : public false_type {};
template < class T >
struct is_integral< const T > : public is_integral< T > {};

template <>
struct is_integral< bool > : public true_type {};
template <>
struct is_integral< char > : public true_type {};
template <>
struct is_integral< wchar_t > : public true_type {};
template <>
struct is_integral< short > : public true_type {};
template <>
struct is_integral< int > : public true_type {};
template <>
struct is_integral< long > : public true_type {};
template <>
struct is_integral< long long > : public true_type {};

template <>
struct is_integral< unsigned char > : public true_type {};
template <>
struct is_integral< unsigned short > : public true_type {};
template <>
struct is_integral< unsigned int > : public true_type {};
template <>
struct is_integral< unsigned long > : public true_type {};
template <>
struct is_integral< unsigned long long > : public true_type {};

template <>
struct is_integral< signed char > : public true_type {};

} // namespace ft

#endif /* IS_INTEGRAL_HPP */
