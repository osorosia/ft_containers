#ifndef ENABLE_IF_HPP
#define ENABLE_IF_HPP

namespace ft {

// https://en.cppreference.com/w/cpp/types/enable_if
template < bool B, class T = void >
struct enable_if {};

template < class T >
struct enable_if< true, T > {
    typedef T type;
};

} // namespace ft

#endif /* ENABLE_IF_HPP */
