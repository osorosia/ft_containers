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
    typedef Key                               key_type;
    typedef T                                 mapped_type;
    typedef std::pair< const Key, T >         value_type;
    typedef std::size_t                       size_type;
    typedef std::ptrdiff_t                    difference_type;
    typedef Compare                           key_compare;
    typedef Allocator                         allocator_type;
    typedef value_type&                       reference;
    typedef const value_type&                 const_reference;
    typedef typename Allocator::pointer       pointer;
    typedef typename Allocator::const_pointer const_pointer;

    typedef typename ft::AvlTree< Key, T, Compare, Allocator >::iterator       iterator;
    typedef typename ft::AvlTree< Key, T, Compare, Allocator >::const_iterator const_iterator;

    typedef std::reverse_iterator< iterator >       reverse_iterator;
    typedef std::reverse_iterator< const_iterator > const_reverse_iterator;

private:
    typedef ft::AvlTree< Key, T, Compare, Allocator > tree_type;
    tree_type                                         tree_;

public:
    //
    // Member classes
    //
    // value_compare

    //
    // Member functions
    //
    // (constructor)
    map()
        : tree_(tree_type()) {}
    explicit map(const Compare& comp, const Allocator& alloc = Allocator()); // TODO:
    // (destructor)
    // operator=
    // get_allocator

    //
    // Element access
    //
    T& at(const Key& key) {
        iterator it = tree_->find(key);
        if (it == tree_->end())
            throw std::out_of_range("map::at");
        return (*it).second;
    }
    const T& at(const Key& key) const {
        iterator it = tree_->find(key);
        if (it == tree_->end())
            throw std::out_of_range("map::at");
        return (*it).second;
    }

    T& operator[](const Key& key) {
        iterator it = tree_->find(key);
        if (it == tree_->end()) {
            iterator ret = tree_->insert(std::pair< Key, T >(key, T())).first;
            return (*ret).second();
        }
        return (*it).second;
    }

    //
    // Iterators
    //
    iterator       begin() { return tree_->begin(); }
    const_iterator begin() const { return tree_->begin(); }

    iterator       end() { return tree_->end(); }
    const_iterator end() const { return tree_->end(); }

    reverse_iterator       rbegin() { return tree_->rbegin(); }
    const_reverse_iterator rbegin() const { return tree_->rbegin(); }

    reverse_iterator       rend() { return tree_->rend(); }
    const_reverse_iterator rend() const { return tree_->rend(); }

    //
    // Capacity
    //
    bool      empty() { return begin() == end(); }
    size_type size() const { return tree_->size(); }
    size_type max_size() const { return tree_->max_size(); }

    //
    // Modifiers
    //
    void clear() { tree_->clear(); }

    std::pair< iterator, bool > insert(const value_type& value) { return tree_->insert(value); }
    iterator insert(iterator pos, const value_type& value) { return tree_->insert(pos, value); }
    template < class InputIt >
    void insert(InputIt first, InputIt last) {
        return tree_->insert(first, last);
    }

    iterator  erase(iterator pos) { return tree_->erase(pos); }
    iterator  erase(iterator first, iterator last) { return tree_->erase(first, last); }
    size_type erase(const Key& key) { return tree_->erase(key); }

    // TODO:
    void swap(map& other);

    //
    // Lookup
    //
    size_type count(const Key& key) const { return tree_->count(key); }

    iterator       find(const Key& key) { return tree_->find(key); }
    const_iterator find(const Key& key) const { return tree_->find(key); }

    std::pair< iterator, iterator > equal_range(const Key& key) { return tree_->equal_range(key); }
    std::pair< const_iterator, const_iterator > equal_range(const Key& key) const {
        return tree_->equal_range(key);
    }

    iterator       lower_bound(const Key& key) { return tree_->lower_bound(key); }
    const_iterator lower_bound(const Key& key) const { return tree_->lower_bound(key); }

    iterator       upper_bound(const Key& key) { return tree_->upper_bound(key); }
    const_iterator upper_bound(const Key& key) const { return tree_->upper_bound(key); }

    //
    // Observers
    //
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
