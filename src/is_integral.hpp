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
struct is_integral;

} // namespace ft

#endif /* IS_INTEGRAL_HPP */
