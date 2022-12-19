#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <memory>

namespace ft {

// https://en.cppreference.com/w/cpp/container/vector
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
    // TODO: std -> ft
    typedef std::reverse_iterator< iterator > reverse_iterator;
    // TODO: std -> ft
    typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

    pointer        begin_;
    pointer        end_;
    pointer        end_cap_;
    allocator_type alloc_;

  public:
    //
    // Member functions
    //

    // (Non title)
    // TODO: (constructor)
    vector() : begin_(NULL), end_(NULL), end_cap_(NULL), alloc_(Allocator()) {}
    explicit vector(const Allocator& alloc)
        : begin_(NULL), end_(NULL), end_cap_(NULL), alloc_(alloc) {}
    // explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
    //     : begin_(NULL), end_(NULL), end_cap_(NULL), alloc_(alloc) {}
    // template < class InputIt >
    // vector(InputIt first, InputIt last, const Allocator& alloc = Allocator());
    // vector( const vector& other );
    // TODO: (destructor)
    // TODO: operator=
    // TODO: assign
    // TODO: get_allocator

    // Element access
    // TODO: at(): out_of_rangeを追加
    reference       at(size_type pos) { return *this[pos]; }
    const_reference at(size_type pos) const { return *this[pos]; }
    reference       operator[](size_type pos) { return begin_ + pos; }
    reference       operator[](size_type pos) const { return begin_ + pos; }
    reference       front() { return *begin_; }
    const_reference front() const { return *begin_; }
    // TODO: back
    // TODO: data

    // Iterators
    // TODO: begin
    // TODO: end
    // TODO: rbegin
    // TODO: rend

    // Capacity
    bool      empty() const { return begin_ == end_; }
    size_type size() const { return end_ - begin_; }
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
