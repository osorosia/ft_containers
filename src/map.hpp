#ifndef MAP_HPP
#define MAP_HPP

#include "tree/avl_tree.h"
#include <functional>
#include <memory>

namespace ft {

// https://en.cppreference.com/w/cpp/container/map
template < class Key,
           class T,
           class Compare   = std::less< Key >,
           class Allocator = std::allocator< std::pair< const Key, T > > >
class map {
protected:
    //
    // Member types
    //
    typedef Key                                                 key_type;
    typedef T                                                   mapped_type;
    typedef std::pair< const Key, T >                           value_type;
    typedef std::size_t                                         size_type;
    typedef std::ptrdiff_t                                      difference_type;
    typedef Compare                                             key_compare;
    typedef Allocator                                           allocator_type;
    typedef value_type&                                         reference;
    typedef const value_type&                                   const_reference;
    typedef typename Allocator::pointer                         pointer;
    typedef typename Allocator::const_pointer                   const_pointer;
    typedef ft::AVLTree< Key, T, Compare, Allocater >::iterator iterator;
    typedef std::reverse_iterator< iterator >                   reverse_iterator;
    // const_iterator
    // typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

    // 
    // Member classes
    // 
    // value_compare

    //
    // Member functions
    //
    // (constructor)
    // (destructor)
    // operator=
    // get_allocator

    // Element access
    // at
    // operator[]

    // Iterators
    // begin
    // end
    // rbegin
    // rend

    // Capacity
    // empty
    // size
    // max_size

    // Modifiers
    // clear
    // insert
    // erase
    // swap

    // Lookup
    // count
    // find
    // equal_range
    // lower_bound
    // upper_bound

    // Observers
    // key_comp
    // value_comp
};

// 
// Non-member functions
// 
// operator==
// operator!=
// operator<
// operator<=
// operator>
// operator>=
// swap

} // namespace ft

#endif /* MAP_HPP */
