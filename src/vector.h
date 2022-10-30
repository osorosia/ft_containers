#ifndef VECTOR_H
#define VECTOR_H

#include <memory>

namespace ft {
template <class T, class Allocator = std::allocator<T> > class vector {
  public:
    typedef T value_type;
    typedef Allocator allocator_type;
    typedef size_t size_type;

  private:
};
} // namespace ft

#endif /* VECTOR_H */
