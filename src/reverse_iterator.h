#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

#include "iterator_traits.h"

namespace ft {

template < class Iter >
class reverse_iterator {
  public:
    typedef Iter                                                    iterator_type;
    typedef typename ft::iterator_traits< Iter >::iterator_category iterator_category;
    typedef typename ft::iterator_traits< Iter >::value_type        value_type;
    typedef typename ft::iterator_traits< Iter >::difference_type   difference_type;
    typedef typename ft::iterator_traits< Iter >::pointer           pointer;
    typedef typename ft::iterator_traits< Iter >::reference         reference;

    reverse_iterator() : it_() {
    }

    ~reverse_iterator() {
    }

    reverse_iterator& operator=(const reverse_iterator< Iter >& other) {
        return *this;
    }

  protected:
    iterator_type it_;
};

} // namespace ft

#endif /* REVERSE_ITERATOR_H */
