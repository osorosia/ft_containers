#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "utils.hpp"
#include <memory>

namespace ft {

// https://en.cppreference.com/w/cpp/container/vector
template < class T, class Allocator = std::allocator< T > >
class vector {
public:
    //
    // Member types
    //
    typedef T                                      value_type;
    typedef Allocator                              allocator_type;
    typedef std::size_t                            size_type;
    typedef std::ptrdiff_t                         different_type;
    typedef value_type&                            reference;
    typedef const value_type&                      const_reference;
    typedef typename Allocator::pointer            pointer;
    typedef const typename Allocator::pointer      const_pointer;
    typedef pointer                                iterator;
    typedef const_pointer                          const_iterator;
    typedef ft::reverse_iterator< iterator >       reverse_iterator;
    typedef ft::reverse_iterator< const_iterator > const_reverse_iterator;

    pointer        begin_;
    pointer        end_;
    pointer        end_cap_;
    allocator_type alloc_;

    //
    // Member functions
    //
    vector()
        : begin_(NULL)
        , end_(NULL)
        , end_cap_(NULL)
        , alloc_(allocator_type()) {}
    explicit vector(const Allocator& alloc)
        : begin_(NULL)
        , end_(NULL)
        , end_cap_(NULL)
        , alloc_(alloc) {}
    explicit vector(size_type count, const T& value = T(), const Allocator& alloc = Allocator())
        : begin_(NULL)
        , end_(NULL)
        , end_cap_(NULL)
        , alloc_(alloc) {
        resize(count, value);
    }
    template < class InputIt >
    vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
        : begin_(NULL)
        , end_(NULL)
        , end_cap_(NULL)
        , alloc_(alloc) {
        assign(first, last);
    }
    vector(const vector& other)
        : begin_(NULL)
        , end_(NULL)
        , end_cap_(NULL)
        , alloc_(other.alloc_) {
        *this = other;
    }

    ~vector() {
        clear();
        alloc_deallocate();
    }

    vector& operator=(const vector& other) {
        if (this == &other)
            return *this;
        resize(other.size());
        for (size_type i = 0; i < other.size(); i++) {
            begin_[i] = other[i];
        }
        return *this;
    }

    void assign(size_type count, const T& value) {
        clear();
        for (size_type i = 0; i < count; i++) {
            push_back(value);
        }
    }
    template < class InputIt >
    typename ft::enable_if< !ft::is_integral< InputIt >::value, void >::type assign(InputIt first,
                                                                                    InputIt last) {
        clear();
        for (iterator it = first; it != last; it++) {
            push_back(*it);
        }
    }

    allocator_type get_allocator() const { return alloc_; }

    //
    // Element access
    //
    reference at(size_type pos) {
        if (pos >= size())
            throw std::out_of_range("vector");
        return begin_[pos];
    }
    const_reference at(size_type pos) const {
        if (pos >= size())
            throw std::out_of_range("vector");
        return begin_[pos];
    }

    reference operator[](size_type pos) { return *(begin_ + pos); }
    reference operator[](size_type pos) const { return *(begin_ + pos); }

    reference       front() { return *begin_; }
    const_reference front() const { return *begin_; }

    reference       back() { return *(end_ - 1); }
    const_reference back() const { return *(end_ - 1); };

    T*       data() { return begin_; }
    const T* data() const { return begin_; };

    //
    // Iterators
    //
    iterator       begin() { return begin_; }
    const_iterator begin() const { return begin_; }

    iterator       end() { return end_; }
    const_iterator end() const { return end_; }

    reverse_iterator       rbegin() { return reverse_iterator(end_); }
    const_reverse_iterator rbegin() const { return const_reverse_iterator(end_); }

    reverse_iterator       rend() { return reverse_iterator(begin_); }
    const_reverse_iterator rend() const { return const_reverse_iterator(begin_); }

    //
    // Capacity
    //
    bool empty() const { return begin_ == end_; }

    size_type size() const { return end_ - begin_; }

    size_type max_size() const { return alloc_.max_size(); }

    // https://cpp.rainy.me/034-vector-memory-allocation.html#reserve%E3%81%AE%E5%AE%9F%E8%A3%85
    void reserve(size_type new_cap) {
        if (new_cap <= capacity())
            return;

        pointer   ptr       = alloc_.allocate(new_cap);
        pointer   old_begin = begin_;
        pointer   old_end   = end_;
        size_type old_cap   = capacity();

        begin_   = ptr;
        end_     = begin_;
        end_cap_ = begin_ + new_cap;

        for (pointer old_iter = old_begin; old_iter != old_end; old_iter++, end_++) {
            alloc_construct(end_, *old_iter);
            alloc_destroy(old_iter);
        }

        alloc_deallocate(old_begin, old_cap);
    }

    size_type capacity() const { return end_cap_ - begin_; }

    //
    // Modifiers
    //
    void clear() {
        size_type sz = size();
        for (size_type i = 0; i < sz; i++) {
            alloc_destroy(--end_);
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
        alloc_construct(end_++, value);
    }

    void pop_back() {
        // undefined behavior: Calling pop_back on an empty container
        alloc_destroy(--end_);
    }

    void resize(size_type count, T value = T()) {
        if (count < size()) {
            for (iterator it = begin_ + count; it != end_; it++) {
                alloc_destroy(it);
            }
            end_ = begin_ + count;
        } else if (count > size()) {
            // TODO: fix performance
            reserve(count);
            for (; size() < count; end_++) {
                alloc_construct(end_, value);
            }
        }
    }

    void swap(vector& other) {
        pointer        begin_tmp   = other.begin_;
        pointer        end_tmp     = other.end_;
        pointer        end_cap_tmp = other.end_cap_;
        allocator_type alloc_tmp   = other.alloc_;

        other.begin_   = begin_;
        other.end_     = end_;
        other.end_cap_ = end_cap_;
        other.alloc_   = alloc_;

        begin_   = begin_tmp;
        end_     = end_tmp;
        end_cap_ = end_cap_tmp;
        alloc_   = alloc_tmp;
    }

private:
    void destroy_until(reverse_iterator rend) {
        for (reverse_iterator riter = rbegin(); riter != rend; riter++, end_--) {
            // &*riter: reverse_iterator -> pointer
            alloc_destroy(&*riter);
        }
    }
    void    alloc_construct(pointer p, const_reference val) { alloc_.construct(p, val); }
    void    alloc_destroy(pointer p) { alloc_.destroy(p); }
    pointer alloc_allocate(size_type n) { alloc_.allocate(n); }
    void    alloc_deallocate() { alloc_.deallocate(begin_, capacity()); }
    void    alloc_deallocate(pointer p, size_type n) { alloc_.deallocate(p, n); }
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
