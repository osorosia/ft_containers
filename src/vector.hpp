#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"
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

    pointer begin_;
    pointer end_;
    pointer end_cap_;
    // https://en.cppreference.com/w/cpp/memory/allocator
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
    vector &operator=(const vector& other) {
        if (*this == other)
            return *this;
        assign(other.begin(), other.end());
        return *this;
    }
    void assign(size_type count, const T& value) {
        if (count > capacity()) {
            // TODO: fix perf
            reserve(count);
        }
        for (iterator it = begin_; it < begin_ + count; it++) {
            if (it >= end_) {
                alloc_.construct(it, value);
            } else {
                *it = value;
            }
        }
        while (size() > count) {
            pop_back();
        }
    }
    template < class InputIt >
    void assign(InputIt first, InputIt last) {
        size_type count = last - first;
        if (count > capacity()) {
            // TODO: fix perf
            reserve(count);
        }
        for (iterator it = begin_; it < begin + count; it++, first++) {
            if (it >= end_) {
                alloc_.construct(it, *first);
            } else {
                *it = *first;
            }
        }
        while (size() > count) {
            pop_back();
        }
    }
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
    // https://cpp.rainy.me/034-vector-memory-allocation.html#reserve%E3%81%AE%E5%AE%9F%E8%A3%85
    void reserve(size_type new_cap) {
        if (new_cap <= capacity())
            return;

        pointer ptr       = alloc_.allocate(new_cap);
        pointer old_begin = begin_;
        pointer old_end   = end_;
        pointer old_cap   = capacity();

        begin_   = ptr;
        end_     = begin_;
        end_cap_ = begin_ + new_cap;

        for (pointer old_iter = old_begin; old_iter != old_end; old_iter++, end_++) {
            alloc_.construct(end_, *old_iter);
            alloc_.destroy(old_iter);
        }

        alloc_.deallocate(old_begin, old_cap);
    }
    size_type capacity() const { return end_cap_ - begin_; }

    // Modifiers
    void clear() {
        size_type sz = size();
        for (size_type i = 0; i < sz; i++) {
            alloc_.destroy(--end_);
        }
    }
    iterator insert(const_iterator pos, const T& value) {
        // TODO:
        return NULL;
    }
    iterator insert(const_iterator pos, size_type count, const T& value) {
        // TODO:
        return NULL;
    }
    template < class InputIt >
    iterator insert(const_iterator pos, InputIt first, InputIt last) {
        // TODO:
        return NULL;
    }
    iterator erase(iterator pos) {
        // TODO:
        return NULL;
    };
    iterator erase(iterator first, iterator last) {
        // TODO:
        return NULL;
    };
    void push_back(const T& value) {
        if (size() + 1 > capacity()) {
            // TODO: fix performance
            reserve(size() + 1);
        }
        alloc_.construct(end_++, value);
    }
    void pop_back() {
        // undefined behavior: Calling pop_back on an empty container
        alloc_.destroy(--end_);
    }
    void resize(size_type count, T value = T()) {
        if (count < size()) {
            for (iterator it = begin_ + count; it != end_; it++) {
                alloc_.destroy(it);
            }
            end_ = begin_ + count;
        } else if (count > size()) {
            // TODO: fix performance
            reserve(count);
            for (; size() < count; end_++) {
                alloc_.construct(end_, value);
            }
        }
    }
    void swap(vector& other) {
        // TODO:
    }

private:
    //
    // Private
    //
    void destroy_until(reverse_iterator rend) {
        for (reverse_iterator riter = rbegin(); riter != rend; riter++, end_--) {
            // &*riter: reverse_iterator -> pointer
            alloc_.destroy(&*riter);
        }
    }
};

//
// Non member functions
//
template < class T, class Alloc >
bool operator==(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs) {
    return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template < class T, class Alloc >
bool operator!=(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs) {
    return !(lhs == rhs);
}
template < class T, class Alloc >
bool operator<(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs) {
    return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}
template < class T, class Alloc >
bool operator<=(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs) {
    return !(rhs < lhs);
}
template < class T, class Alloc >
bool operator>(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs) {
    return rhs < lhs;
}
template < class T, class Alloc >
bool operator>=(const ft::vector< T, Alloc >& lhs, const ft::vector< T, Alloc >& rhs) {
    return !(lhs < rhs);
}
template < class T, class Alloc >
void swap(ft::vector< T, Alloc >& lhs, ft::vector< T, Alloc >& rhs) {
    lhs.swap(rhs);
}

} // namespace ft

#endif /* VECTOR_HPP */
