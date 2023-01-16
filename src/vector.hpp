#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "equal.hpp"
#include "lexicographical_compare.hpp"
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
    allocator_type get_allocator() const { return alloc_; }

    // Element access
    reference at(size_type pos) {
        if (pos >= size())
            throw std::out_of_range("vector");
        return *this[pos];
    }
    const_reference at(size_type pos) const {
        if (pos >= size())
            throw std::out_of_range("vector");
        return *this[pos];
    }
    reference       operator[](size_type pos) { return begin_ + pos; }
    reference       operator[](size_type pos) const { return begin_ + pos; }
    reference       front() { return *begin_; }
    const_reference front() const { return *begin_; }
    reference       back() { return *(end_ - 1); }
    const_reference back() const { return *(end_ - 1); };
    T*              data() { return begin_; }
    const T*        data() const { return begin_; };

    // Iterators
    iterator               begin() { return begin_; }
    const_iterator         begin() const { return begin_; }
    iterator               end() { return end_; }
    const_iterator         end() const { return end_; }
    reverse_iterator       rbegin() { return reverse_iterator(end_); }
    const_reverse_iterator rbegin() const { return reverse_iterator(end_); }
    reverse_iterator       rend() { return reverse_iterator(begin_); }
    const_reverse_iterator rend() const { return reverse_iterator(begin_); }

    // Capacity
    bool      empty() const { return begin_ == end_; }
    size_type size() const { return end_ - begin_; }
    size_type max_size() const { return alloc_.max_size(); }
    // TODO: reserve
    // void      reserve(size_type new_cap);
    size_type capacity() const { return end_cap_ - begin_; }

    // Modifiers
    // TODO: clear
    // TODO: insert
    // TODO: erase
    // TODO: push_back
    // TODO: pop_back
    // TODO: resize
    // TODO: swap
    void swap(vector& other) {}

  private:
    //
    // Private
    //
};

//
// Non member functions
//
template < class T, class Alloc >
bool operator==(const std::vector< T, Alloc >& lhs, const std::vector< T, Alloc >& rhs) {
    return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template < class T, class Alloc >
bool operator!=(const std::vector< T, Alloc >& lhs, const std::vector< T, Alloc >& rhs) {
    return !(lhs == rhs);
}
template < class T, class Alloc >
bool operator<(const std::vector< T, Alloc >& lhs, const std::vector< T, Alloc >& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template < class T, class Alloc >
bool operator<=(const std::vector< T, Alloc >& lhs, const std::vector< T, Alloc >& rhs) {
    return !(rhs < lhs);
}
template < class T, class Alloc >
bool operator>(const std::vector< T, Alloc >& lhs, const std::vector< T, Alloc >& rhs) {
    return rhs < lhs;
}
template < class T, class Alloc >
bool operator>=(const std::vector< T, Alloc >& lhs, const std::vector< T, Alloc >& rhs) {
    return !(lhs < rhs);
}
template < class T, class Alloc >
void swap(std::vector< T, Alloc >& lhs, std::vector< T, Alloc >& rhs) {
  lhs.swap(rhs);
}

} // namespace ft

#endif /* VECTOR_HPP */
