#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

namespace ft {

template < class T, class Allocator = std::allocator< T > >
class vector {
  protected:
    typedef T                                 value_type;
    typedef Allocator                         allocator_type;
    typedef std::size_t                       size_type;
    typedef std::ptrdiff_t                    different_type;
    typedef value_type                       &reference;
    typedef const value_type                 &const_reference;
    typedef typename Allocator::pointer       pointer;
    typedef const typename Allocator::pointer const_pointer;
    typedef pointer                           iterator;
    typedef const_pointer                     const_iterator;

    pointer begin_;
    pointer end_;

  public:
    reference at(size_type pos) {
        return *this[pos];
    }

    reference operator[](size_type pos) {
        return begin_ + pos;
    }
};

} // namespace ft

#endif /* VECTOR_H */
