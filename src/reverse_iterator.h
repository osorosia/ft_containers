#ifndef REVERSE_ITERATOR_H
#define REVERSE_ITERATOR_H

namespace ft {

template < class Iter >
class reverse_iterator {
  public:
    typedef typename Iter                                            iterator_type;
    typedef typename std::iterator_traits< Iter >::iterator_category iterator_category;
    typedef typename std::iterator_traits< Iter >::value_type        value_type;
    typedef typename std::iterator_traits< Iter >::difference_type   difference_type;
    typedef typename std::iterator_traits< Iter >::pointer           pointer;
    typedef typename std::iterator_traits< Iter >::reference         reference;

    reverse_iterator() {
    }
    ~reverse_iterator() {
    }

  protected:
};

} // namespace ft

#endif /* REVERSE_ITERATOR_H */
