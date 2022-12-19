#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft {

template < class T, class Allocator = std::allocator< T > >
class vector {
  protected:
    //
    // Member types
    //
    typedef T                                 value_type;
    typedef Allocator                         allocator_type;
    typedef std::size_t                       size_type;
    typedef std::ptrdiff_t                    different_type;
    typedef value_type&                       reference;
    typedef const value_type&                 const_reference;
    typedef typename Allocator::pointer       pointer;
    typedef const typename Allocator::pointer const_pointer;
    typedef pointer                           iterator;
    typedef const_pointer                     const_iterator;
    // TODO: iterator
    // TODO: const_iterator
    // TODO: reverse_iterator
    // TODO: const_reverse_iterator

    pointer begin_;
    pointer end_;

  public:
    //
    // Member functions
    //

    // (Non title)
    // TODO: (constructor)
    // TODO: (destructor)
    // TODO: operator=
    // TODO: assign
    // TODO: get_allocator

    // Element access
    reference       at(size_type pos) { return *this[pos]; }
    reference       operator[](size_type pos) { return begin_ + pos; }
    reference       front() const { return *front_; }
    const_reference front() const { return *front_; }
    // TODO: back
    // TODO: data

    // Iterators
    // TODO: begin
    // TODO: end
    // TODO: rbegin
    // TODO: rend

    // Capacity
    // TODO: empty
    // TODO: size
    // TODO: max_size
    // TODO: reserve
    // TODO: capacity

    // Modifiers
    // TODO: clear
    // TODO: insert
    // TODO: erase
    // TODO: push_back
    // TODO: pop_back
    // TODO: resize
    // TODO: swap
};

// 
// Non member functions
// 
// TODO: operator==
// TODO: operator!=
// TODO: operator<
// TODO: operator<=
// TODO: operator>
// TODO: operator>=
// TODO: std::swap

} // namespace ft

#endif /* VECTOR_HPP */
