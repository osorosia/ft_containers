#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

namespace ft {

template < class Iter >
struct iterator_traits {
    typedef typename Iter::difference_type   difference_type;
    typedef typename Iter::value_type        value_type;
    typedef typename Iter::pointer           pointer;
    typedef typename Iter::reference         reference;
    typedef typename Iter::iterator_category iterator_category;
};

} // namespace ft

#endif /* ITERATOR_TRAITS_H */
